//index.js
const app = getApp()

Page({
  data: {
    avatarUrl: './user-unlogin.png',
    userInfo: {},
    logged: false,
    takeSession: false,
    requestResult: '',
    goods: [ ],
    goodsIndex: [],
    types: [], //'衣服', '鞋子'
    types_titles: {},
    showTypes: false,
    showGoods: true,
    keyword: ""
  },

  onLoad: function() {
    var page = this;
    if (!wx.cloud) {
      wx.redirectTo({
        url: '../chooseLib/chooseLib',
      })
      return
    }

    console.log(111111);
    const db = wx.cloud.database()
    db.collection('goods_index').get({
      success: res => {
        // this.setData({
        //  queryResult: JSON.stringify(res.data, null, 2)
        //})
        //console.log('[数据库] [查询记录] 成功: ', res)
        console.log(res.data);
        page.setData({goodsIndex:res.data});
        for (var i=0;i<res.data.length;i++){
          page.data.types.push(res.data[i].type);
        }
        page.setData({
          types: page.data.types
        });
      },
      fail: err => {
        console.log(err);
      }
    });
    db.collection('goods').get({
      success: res => {
        // this.setData({
        //  queryResult: JSON.stringify(res.data, null, 2)
        //})
        //console.log('[数据库] [查询记录] 成功: ', res)
        console.log(res);
        page.setData({ goods: res.data });

      },
      fail: err => {
        console.log(err);
      }
    });
    console.log(this.data.types);
    for (var i = 0; i < this.data.types.length; i++) {
      let _type = this.data.types[i];
      console.log(_type);
      db.collection('goods_index').where(
        { type: _type }
      ).get({
        success: res => {
          console.log('get titles:'+_type);
          console.log(res.data);
          page.data.types.push(_type);
          page.data.types_titles[_type] = res.data[0].titles;
        },
        fail: err => {
          console.log(err);
        }
      });
    }
    
    // 获取用户信息
    wx.getSetting({
      success: res => {
        if (res.authSetting['scope.userInfo']) {
          // 已经授权，可以直接调用 getUserInfo 获取头像昵称，不会弹框
          wx.getUserInfo({
            success: res => {
              this.setData({
                avatarUrl: res.userInfo.avatarUrl,
                userInfo: res.userInfo
              })
            }
          })
        }
      }
    })
  },
  clickSearch: function (e) {
    this.setData({showTypes:true, showGoods:false});
  },
  updateKeyword: function(e){
    var val = e.detail.value;
    this.setData({
      keyword: val
    });
  },
  tbSearch: function (e) {
    var page = this;
    this.setData({ showTypes: false, showGoods: true });
    const db = wx.cloud.database();
    console.log("----titles--->");
    console.log(this.data.types_titles);
    page.setData({
      goods: []
    });
    for (var i=0; i<this.data.types.length; i++){
      let _type = page.data.types[i];
      let _value = page.data.types_titles[_type];
      let goods = [];
      if (_value.indexOf(page.data.keyword) >= 0){
        console.log('search hit....'+page.data.keyword);
        db.collection('goods').where(
          { type: _type }
        ).get({
          success: res => {
            console.log(res.data);
            for (var j=0; j<res.data.length; j++){
              if (res.data[j].title.indexOf(page.data.keyword) >= 0){
                console.log('hithit');
                goods.push(res.data[j]);
              }
            }
            page.setData({
              goods: page.data.goods.concat(goods)
            });
          },
          fail: err => {
            console.log(err);
          }
        }); 
      }
    }
  },
  typeSearch: function(e){
    this.setData({ showTypes: false, showGoods: true });
    var page=this;
    const db = wx.cloud.database();
    let _type = e.currentTarget.dataset.type;
    console.log(_type);
    db.collection('goods').where(
      { type: _type }
    ).get({
      success: res => {
        page.setData({
          goods: res.data
        });
      },
      fail: err => {
        console.log(err);
      }
    }); 
  },
  copyQuanter: function (e, code) {
    wx.setClipboardData({
      data: e.currentTarget.dataset.code,
    });
    wx.showModal({
      title: '温馨提示',
      content: "复制成功！打开手机淘宝下单吧～",
      success: function (res) {
        if (res.confirm) {
          console.log('用户点击确定')
        } else if (res.cancel) {
          console.log('用户点击取消')
        }
      }
    })
  },
  update_goods_index: function(e) {
    const db = wx.cloud.database();
    console.log(this.data.types);
    for(var i=0;i<this.data.types.length;i++)
    {
      var _type = this.data.types[i];
      console.log(_type);
      db.collection('goods').where(
        {type:_type}
      ).get({
        success: res => {
          // this.setData({
          //  queryResult: JSON.stringify(res.data, null, 2)
          //})
          //console.log('[数据库] [查询记录] 成功: ', res)
          var titles = "";
          for (var j=0;j<res.data.length;j++){
            titles += res.data[j].title + "__";
          }
          console.log(titles);
          db.collection('goods_index').where(
            { type: _type }
          ).get({
            success: res2 => {
              console.log('res2');
              console.log(res2.data);
              if (res2.data.length > 0){
                console.log("hit---->");
              }
            }
          });
          db.collection('goods_index').where(
            { type: _type }
          ).update({data:
          {
            titles:titles
          }});
          //page.setData({ goodsIndex: res.data });

        },
        fail: err => {
          console.log(err);
        }
      });      
    }
  },
    update_goods_index: function(e) {
    const db = wx.cloud.database();
    console.log(this.data.types);
    for(var i=0;i<this.data.types.length;i++)
    {
      var _type = this.data.types[i];
      console.log(_type);
      db.collection('goods').where(
        {type:_type}
      ).get({
        success: res => {
          // this.setData({
          //  queryResult: JSON.stringify(res.data, null, 2)
          //})
          //console.log('[数据库] [查询记录] 成功: ', res)
          var titles = "";
          for (var j=0;j<res.data.length;j++){
            titles += res.data[j].title + "__";
          }
          console.log(titles);
          db.collection('goods_index').where(
            { type: _type }
          ).get({
            success: res2 => {
              console.log('res2');
              console.log(res2.data);
              if (res2.data.length > 0){
                console.log("hit---->");
              }
            }
          });
          db.collection('goods_index').where(
            { type: _type }
          ).update({data:
          {
            titles:titles
          }});
          //page.setData({ goodsIndex: res.data });

        },
        fail: err => {
          console.log(err);
        }
      });      
    }
  },

  onGetUserInfo: function(e) {
    if (!this.logged && e.detail.userInfo) {
      this.setData({
        logged: true,
        avatarUrl: e.detail.userInfo.avatarUrl,
        userInfo: e.detail.userInfo
      })
    }
  },

  onGetOpenid: function() {
    // 调用云函数
    wx.cloud.callFunction({
      name: 'login',
      data: {},
      success: res => {
        console.log('[云函数] [login] user openid: ', res.result.openid)
        app.globalData.openid = res.result.openid
        wx.navigateTo({
          url: '../userConsole/userConsole',
        })
      },
      fail: err => {
        console.error('[云函数] [login] 调用失败', err)
        wx.navigateTo({
          url: '../deployFunctions/deployFunctions',
        })
      }
    })
  },

  // 上传图片
  doUpload: function () {
    // 选择图片
    wx.chooseImage({
      count: 1,
      sizeType: ['compressed'],
      sourceType: ['album', 'camera'],
      success: function (res) {

        wx.showLoading({
          title: '上传中',
        })

        const filePath = res.tempFilePaths[0]
        
        // 上传图片
        const cloudPath = 'my-image' + filePath.match(/\.[^.]+?$/)[0]
        wx.cloud.uploadFile({
          cloudPath,
          filePath,
          success: res => {
            console.log('[上传文件] 成功：', res)

            app.globalData.fileID = res.fileID
            app.globalData.cloudPath = cloudPath
            app.globalData.imagePath = filePath
            
            wx.navigateTo({
              url: '../storageConsole/storageConsole'
            })
          },
          fail: e => {
            console.error('[上传文件] 失败：', e)
            wx.showToast({
              icon: 'none',
              title: '上传失败',
            })
          },
          complete: () => {
            wx.hideLoading()
          }
        })

      },
      fail: e => {
        console.error(e)
      }
    })
  },

})
