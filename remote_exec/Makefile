# vim:noet ts=8 sw=8 is si
SALMON_HOME:=$(shell pwd)
BRANCH:=$(shell svn info |grep -e "^URL:" |sed 's|^.*/||')
BUILDDATE:=$(shell date +%Y%m%d_%H%M%S)
REPOS_VERSION:=v$(shell svn info |grep -e "^Last Changed Rev:" | cut -d' ' -f4)
SALMON_VERSION:=$(BRANCH)-$(REPOS_VERSION)
INSTALL_TARGET:=$(if $(SALMON_INSTALL_TARGET),$(SALMON_INSTALL_TARGET),salmon@10.34.131.134)
RSA_ID:=$(if $(SALMON_INSTALL_RSA),-i $(SALMON_INSTALL_RSA))

.PHONY: all

all: salmon-master

BUILD_ROOT := $(SALMON_HOME)/BUILD
BACKUP_DIR := ~/pkgs-salmon
PACKAGE_ROOT := $(BUILD_ROOT)/$(SALMON_VERSION)
SALMON_PACKAGE  := $(SALMON_VERSION).tar.bz2
NODE_MOD_PACKAGE := node_modules-salmon.tar.bz2
BOWER_COM_PACKAGE := bower_components-salmon.tar.bz2
SALMON_PACKAGES := \
	$(BUILD_ROOT)/$(SALMON_PACKAGE) \
	$(BUILD_ROOT)/$(NODE_MOD_PACKAGE) \
	$(BUILD_ROOT)/$(BOWER_COM_PACKAGE) \
	$(nil)

BACKEND_FILES := \
	bin/*.sql \
	bin/*.sh \
	etc/mysql/*.template \
	cron/* \
	*.py \
	*.xml \
	salmon/*/* \
	salmon/mastersite/*/* \
	$(nil)

BACKEND_DIRS := \
	SalmonBFE \
	$(nil)

NODE_MODULES:= \
	node_modules \
	admin/bower_components \
	static/bower_components \
	$(nil)

TAR_EXCLUDE:= \
	--exclude .svn \
	--exclude node_modules \
	--exclude bower_components \
	--exclude "*.pyc" \
	--exclude ftest \
	--exclude ftest_lxp \
	$(nil)

salmon-master: $(SALMON_PACKAGES)

$(BUILD_ROOT):
	mkdir -p $(BUILD_ROOT)

$(BUILD_ROOT)/$(SALMON_PACKAGE):: Makefile $(BUILD_ROOT) $(BACKEND_FILES) SalmonBFE/*/*/*
	rm -rf $(PACKAGE_ROOT); \
	mkdir -p $(addprefix $(BUILD_ROOT)/,data/salmon_logs httpd-document-root)
	mkdir -p $(addprefix $(PACKAGE_ROOT)/,$(BACKEND_DIRS)); \
	ln -s ../httpd-document-root $(PACKAGE_ROOT)/file-service-root
	ln -s ../data/salmon_uploads $(PACKAGE_ROOT)/uploads
	ln -s ../node_modules ../bower_components $(PACKAGE_ROOT)/
	ln -s ../data/salmon_logs $(PACKAGE_ROOT)/logs
	echo $(SALMON_VERSION) > $(PACKAGE_ROOT)/version; \
	tar -c $(TAR_EXCLUDE) *.xml *.py alterDB bin etc salmon script cron SalmonBFE | tar -xC $(PACKAGE_ROOT); \
	rm -rf $(addprefix $(PACKAGE_ROOT)/SalmonBFE/,logs $NODE_MODULES)
	ln -s ../logs ../node_modules $(PACKAGE_ROOT)/SalmonBFE/
	ln -s ../../bower_components/admin $(PACKAGE_ROOT)/SalmonBFE/admin/bower_components
	ln -s ../../bower_components/static $(PACKAGE_ROOT)/SalmonBFE/static/bower_components
	sed -i 's|9d3cc7d3874249876e96b9b68865cb8b02c50b33|b18a092dedeafe4b351fe0490df31b8d8c547f37|' $(PACKAGE_ROOT)/initial_data.xml; \
	sed -i 's|^var API_PATH_PREFIX .*;|var API_PATH_PREFIX = "/";|' $(PACKAGE_ROOT)/SalmonBFE/admin/manager/script/config_release.js; \
	sed -i "/Database name/s|'NAME':[^#]*#|'NAME': 'salmon',    #|" $(PACKAGE_ROOT)/settings.py; \
	$(PACKAGE_ROOT)/bin/setup-ports.sh -a 8094 -f 8084 -p 80 -h salmon.ucmt.ucweb.local -s 10.34.134.122 -m localhost.ucfly.com -u ucmt.ucweb.local; \
	$(PACKAGE_ROOT)/bin/setup-httpd.sh -S $(PACKAGE_ROOT) -u salmon -g salmon -m chenjb@ucweb.com -a 8094 -f 8084 -p 8080 -s salmon.ucmt.ucweb.local -d /home/salmon/httpd-document-root -r /home/salmon/local/httpd; \
	cd $(BUILD_ROOT) && tar jcf $@ --exclude .svn --exclude "*.pyc" $(SALMON_VERSION)
	#rm -rf $(PACKAGE_ROOT)

$(BUILD_ROOT)/$(NODE_MOD_PACKAGE): SalmonBFE/node_modules
	cd SalmonBFE && tar jcf $@ --exclude .svn node_modules

$(BUILD_ROOT)/$(BOWER_COM_PACKAGE): SalmonBFE/admin/bower_components SalmonBFE/static/bower_components
	mkdir -p $(BUILD_ROOT)/bower_components
	cp -rf SalmonBFE/admin/bower_components $(BUILD_ROOT)/bower_components/admin
	cp -rf SalmonBFE/static/bower_components $(BUILD_ROOT)/bower_components/static
	cd $(BUILD_ROOT) && tar jcf $@ --exclude .svn bower_components

SalmonBFE/node_modules: SalmonBFE/package.json
	cd SalmonBFE && npm install
	touch $@

SalmonBFE/admin/bower_components: SalmonBFE/admin/bower.json
	cd SalmonBFE/admin && bower install
	touch $@

SalmonBFE/static/bower_components: SalmonBFE/static/bower.json
	cd SalmonBFE/static && bower install
	touch $@

INSTALL_COMMANDS:= \
	cd $(BACKUP_DIR); \
	tar jxf $(BACKUP_DIR)/$(SALMON_PACKAGE) $(SALMON_VERSION)/bin/publish_test.sh; \
	cd ~; \
	bash -ix $(BACKUP_DIR)/$(SALMON_VERSION)/bin/publish_test.sh $(SALMON_VERSION); \
	$(nil)

install: salmon-master
	scp $(RSA_ID) -P 9922 $(SALMON_PACKAGES) $(INSTALL_TARGET):$(BACKUP_DIR)
	echo "$(INSTALL_COMMANDS)" | ssh -p 9922 $(RSA_ID) $(INSTALL_TARGET)

clean:
	cd $(SALMON_HOME)/.. && rm salmon-*.tar.bz2
