-- ----------------------------
-- Table structure for `config_uitask`
-- ----------------------------
DROP TABLE IF EXISTS `config_uitask`;
CREATE TABLE `config_uitask` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `product_id` int(11) NOT NULL,
  `description` longtext NOT NULL,
  `owner_id` int(11) NOT NULL,
  `creationdate` date NOT NULL,
  `pkg_count` int(11) NOT NULL,
  `log` longtext NOT NULL,
  `status` varchar(1) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `config_uitask_7f1b40ad` (`product_id`),
  KEY `config_uitask_cb902d83` (`owner_id`),
  CONSTRAINT `owner_id_refs_id_ab425ca4` FOREIGN KEY (`owner_id`) REFERENCES `accounts_user` (`id`),
  CONSTRAINT `product_id_refs_id_e7d8421c` FOREIGN KEY (`product_id`) REFERENCES `product` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of config_uitask
-- ----------------------------

-- ----------------------------
-- Table structure for `config_uitask_packages`
-- ----------------------------
DROP TABLE IF EXISTS `config_uitask_packages`;
CREATE TABLE `config_uitask_packages` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `uitask_id` int(11) NOT NULL,
  `package_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `uitask_id` (`uitask_id`,`package_id`),
  KEY `config_uitask_packages_e87763fe` (`uitask_id`),
  KEY `config_uitask_packages_b6411b91` (`package_id`),
  CONSTRAINT `package_id_refs_id_f5235506` FOREIGN KEY (`package_id`) REFERENCES `package` (`id`),
  CONSTRAINT `uitask_id_refs_id_c4a75fb3` FOREIGN KEY (`uitask_id`) REFERENCES `config_uitask` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of config_uitask_packages
-- ----------------------------
