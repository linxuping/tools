//index.js
const app = getApp()
var types = [];
//var types_titles = {};
var pages = 0;
var openid = '';
var db = wx.cloud.database();

function sort(arr){
  var d=new Date();
  //return arr.sort(function () { return d.getHours()/25 - Math.random() });
  return arr.sort(function () { return 0.5 - Math.random() });
}
//["良品铺子", "运动裤", "百草味", "三只松鼠", "优衣库", "格力", "史密斯", "可优比", "创维", "海底捞", "波司登", "周黑鸭", "三星", "vivo", "大益", "伊利", "五谷磨房", "荣耀", "耐克", "百雀羚", "玉兰油", "小米手机", "华为", "羽绒服", "点读笔", "卫衣", "预留1", "马克华菲", "飞科", "飞利浦", "长虹", "贝亲", "西门子", "裂帛", "英氏", "苏泊尔", "花花公子", "老板电器", "美的", "美特斯邦威", "海尔", "海信", "森马", "格兰仕", "松下", "杰克琼斯", "思莱德", "巴拉巴拉", "安奈儿", "好奇", "太平鸟", "夏普", "全棉时代", "九阳", "七匹狼", "tcl", "魅族", "裂帛", "oppo", "雀巢", "蒙牛"]

function yesterday(num, str) {
  var today = new Date();
  var nowTime = today.getTime();
  var ms = 24 * 3600 * 1000 * num;
  today.setTime(parseInt(nowTime + ms));
  var oYear = today.getFullYear();
  var oMoth = (today.getMonth() + 1).toString();
  if (oMoth.length <= 1) oMoth = '0' + oMoth;
  var oDay = today.getDate().toString();
  if (oDay.length <= 1) oDay = '0' + oDay;
  //return oYear + str + oMoth + str + oDay;
  return oMoth + "月" + oDay + "日";
}

function formatDate(time) {
  var date = new Date(time);
  var year = date.getFullYear(),
    month = date.getMonth() + 1,//月份是从0开始的
    day = date.getDate(),
    hour = date.getHours(),
    min = date.getMinutes(),
    sec = date.getSeconds();
  var newTime = year + '-' +
    (month < 10 ? '0' + month : month) + '-' +
    (day < 10 ? '0' + day : day) + ' ' +
    (hour < 10 ? '0' + hour : hour) + ':' +
    (min < 10 ? '0' + min : min) + ':' +
    (sec < 10 ? '0' + sec : sec);
  return newTime;
}

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
    //types_titles: {},
    showTypes: false,
    showGoods: true,
    typeClicked: false,
    keyword: "",
    curTab: 0,
    current: 0,
    tabList: [{
      id: 1,
      name: "儿童"
    },
    {
      id: 2,
      name: "女性"
    },
    {
      id: 3,
      name: "衣饰"
    }, 
    {
      id: 4,
      name: "吃货"
    },
    {
      id: 5,
      name: "电器"
    },
    {
      id: 6,
      name: "其他"
    }
    ],
    types_class: []
  },

  selectTab(e) {
    let index = e.target.dataset.index;
    console.log(index);
    this.setData({
      curTab: index,
      current: index
    })
  },
  swiperChange(e) {
    let index = e.detail.current;
    this.setData({
      curTab: index,
      current: index
    })
  },

  onLoad: function() {
    wx.cloud.callFunction({
      name: 'login',
      complete: res => {
        console.log('云函数获取到的openid: ', res.result.openid);
        openid = res.result.openid;
      }
    });

    this.setData({
      types_class: types_class
    });

    var page = this;
    if (!wx.cloud) {
      wx.redirectTo({
        url: '../chooseLib/chooseLib',
      })
      return
    }

    db.collection('goods').orderBy('quanter', 'desc').limit(10).get({
      success: res => {
        page.setData({ goods: sort(res.data) });
        console.log(res.data);
      },
      fail: err => {
        console.log(err);
      }
    });
    console.log(this.data.types);

    //const db = wx.cloud.database()
    /*
    for (var k=0; k<4; k++){  //max 20*4
      var query = null;
      if (k == 0)
        query = db.collection('goods_index').orderBy('seq','desc').limit(20);
      else
        query = db.collection('goods_index').orderBy('seq', 'desc').skip(k*20).limit(20);
      query.get({
        success: res => {
          for (var i=0;i<res.data.length;i++){
            types.push(res.data[i].type);
            let _type = res.data[i].type;
            db.collection('goods_index').where(
              { type: _type }
            ).get({
              success: res => {
                types_titles[_type] = res.data[0].titles;
              },
              fail: err => { console.log(err); }
            });
          }
          page.setData({ types: types });
          console.log(types);
        },
        fail: err => { console.log(err); }
      });      
    }*/
    db.collection('goods_index').where(
      { type: "预留1" }
    ).get({
      success: res => {
        types_titles["预留1"] = res.data[0].titles;
      },
      fail: err => { console.log(err); }
    });
    var types = []
    for (var key in types_titles){
      types.push(key);
    }
    page.setData({ types: types });
    
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
    wx.pageScrollTo({
      scrollTop: 0
    })
    this.setData({showTypes:true, showGoods:false});
  },
  updateKeyword: function(e){
    var val = e.detail.value;
    this.setData({
      keyword: val
    });
  },
  tbSearch: function (e) {
    pages = 0;
    var page = this;
    //page.setData({ goods: [] });
    wx.pageScrollTo({
      scrollTop: 0
    })
    this.setData({ showTypes: false, showGoods: true });
    //const db = wx.cloud.database();
    console.log("----titles--->");

    if (openid != "oV5MQ5aN_i_ea9dGxZOHHBC8Bosg"){
      db.collection('search_keywords').add({
        // data 字段表示需新增的 JSON 数据
        data: {
          keyword: page.data.keyword,
          type: 'tb search',
          create_time: formatDate(new Date().getTime())
        }
      }).then(res => {
        console.log(res)
      })
        .catch(console.error)      
    }

    console.log(types_titles);
    if (page.data.keyword.trim().length==0){
      db.collection('goods').orderBy('quanter', 'desc').limit(10).get({
        success: res => {
          page.setData({ goods: res.data });
        },
        fail: err => {
          console.log(err);
        }
      });
      return;
    }
    page.setData({
      goods: []
    });
    wx.showLoading({
      title: '查询中....',
    })
    setTimeout(function(){
      wx.hideLoading();
    },5000);
    var hit = false;
    var all_types = this.data.types;
    all_types.push('预留1');
    var _len = all_types.length;
    console.log(all_types);
    console.log(types_titles);
    for (var i=0; i<_len; i++){
      let _type = all_types[i];
      let _value = types_titles[_type];
      let goods = [];
      if (_value == undefined){
        //page.tbSearch(e);
        console.log("undefi: "+_type);
        continue;
      }
        
      if (_value.indexOf(page.data.keyword) >= 0){
        hit = true;
        console.log('search hit....'+page.data.keyword);
        function query_goods(offset){
          var query = null;
          if (offset == 0)
            query = db.collection('goods').orderBy('quanter', 'desc');
          else
            query = db.collection('goods').orderBy('quanter', 'desc').skip(offset)
          query.where(
            { type: _type }
          ).get({
            success: res => {
              //console.log(res.data);
              for (var j=0; j<res.data.length; j++){
                if (res.data[j].title.indexOf(page.data.keyword) >= 0){
                  console.log('hithit');
                  goods.push(res.data[j]);
                }
              }
              page.setData({
                goods: page.data.goods.concat(goods)
              });
              console.log(_type + ": " + offset.toString() + "->" + res.data.length.toString());
              if (res.data.length == 20){
                if (page.data.goods.length >= 150){
                  console.log(_type + " excceed!");
                }
                else
                  query_goods(offset+20);
              }
              else{
                wx.hideLoading();
              }
            },
            fail: err => { console.log(err); }
          }); 
        }
        query_goods(0)
      }
    }
    if (!hit){
      wx.hideLoading();
      wx.showToast({
        title: '尝试其他词哈～',
      })
    }
  },
  typeSearch: function(e){
    db = wx.cloud.database();
    var page = this;
    //page.setData({ goods: [] });
    wx.pageScrollTo({
      scrollTop: 0
    })
    wx.showLoading({
      title: '查询中....',
    })
    setTimeout(function () {
      wx.hideLoading();
    }, 5000);

    pages = -1;
    let _type = e.currentTarget.dataset.type;
    page.setData({ showTypes: false, showGoods: true, typeClicked: true, goods: [],keyword: ""  });
    console.log(_type);

    if (openid != "oV5MQ5aN_i_ea9dGxZOHHBC8Bosg"){
      db.collection('search_keywords').add({
        // data 字段表示需新增的 JSON 数据
        data: {
          keyword: _type,
          type: 'type',
          create_time: formatDate(new Date().getTime())
        }
      }).then(res => {
        console.log(res)
      })
        .catch(console.error)      
    }


    if (_type == "全部"){
      pages = 0;
      db.collection('goods').orderBy('quanter', 'desc').limit(10).get({
        success: res => {
          page.setData({ goods: res.data, keyword:'' });
          wx.hideLoading();
        },
        fail: err => {
          console.log(err);
        }
      });
      return;
    }

    db.collection('goods').orderBy('quanter', 'desc').limit(5).where(
      { type: _type }
    ).get({
      success: res => {
        page.setData({
          goods: page.data.goods.concat(res.data)
        });
        wx.hideLoading();
      },
      fail: err => { console.log(err); }
    }); 
    function get_goods(offset){
      db.collection('goods').orderBy('quanter', 'desc').skip(offset).limit(20).where(
        { type: _type }
      ).get({
        success: res => {
          page.setData({
            goods: page.data.goods.concat(res.data)
          });
          console.log(offset.toString() + '->' + res.data.length.toString());
          if (res.data.length == 20)
            get_goods(offset+20)
        },
        fail: err => { console.log(err); }
      });      
    }
    get_goods(5)
  },
  copyQuanter: function (e, code) {
    if (openid == "oV5MQ5aN_i_ea9dGxZOHHBC8Bosg") {
      db.collection('click_quanter').add({
        // data 字段表示需新增的 JSON 数据
        data: {
          title: e.currentTarget.dataset.title,
          create_time: formatDate(new Date().getTime())
        }
      }).then(res => {
        console.log(res)
      })
        .catch(console.error)
    }
    wx.setClipboardData({
      data: e.currentTarget.dataset.code,
    });
    wx.showModal({
      title: '温馨提示',
      content: "复制成功！打开手机淘宝下单吧～",
      showCancel: false,
      success: function (res) {
        if (res.confirm) {
          console.log('用户点击确定')
        } else if (res.cancel) {
          console.log('用户点击取消')
        }
      }
    })
  },
  onReachBottom: function(){
    if (pages == -1)
      return;
    this.setData({ typeClicked:false });
    var page = this;
    if (page.data.keyword.trim().length > 0 || page.data.showTypes)
      return;
    //const db = wx.cloud.database();
    pages += 10;
    console.log("offset: "+pages);
    wx.showLoading({
      title: '加载中！稍等哈',
    })
    db.collection('goods').orderBy('quanter', 'desc').skip(pages).limit(10).get({
      success: res => {
        page.setData({ goods: page.data.goods.concat(res.data) });
        wx.hideLoading();
      },
      fail: err => {
        console.log(err);
        wx.hideLoading();
      }
    });
  },
  update_goods_index: function(e) {
    //const db = wx.cloud.database();
    console.log(this.data.types);
    for(var i=0;i<this.data.types.length;i++)
    {
      var _type = this.data.types[i];
      console.log(_type);
      db.collection('goods').orderBy('quanter', 'desc').where(
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
    //const db = wx.cloud.database();
    console.log(this.data.types);
    for(var i=0;i<this.data.types.length;i++)
    {
      var _type = this.data.types[i];
      console.log(_type);
      db.collection('goods').orderBy('quanter', 'desc').where(
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
  onShareAppMessage: function () {
    return {
      title: '至少5元，优惠券每日自动更新',
      desc: '各种类别都有哦～',
      path: '/pages/index/index'
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

  switchRightTab: function (e) {
    // 获取item项的id，和数组的下标值  
    let id = e.target.dataset.id,
      index = parseInt(e.target.dataset.index);
    // 把点击到的某一项，设为当前index  
    this.setData({
      curNav: id,
      curIndex: index
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

var types_titles = {
  "运动裤": "男女同款运动裤秋季修身九分裤男小脚条纹学生班服潮流休闲裤子_秋季装运动裤男士小脚卫裤子青少年休闲长裤束脚学生班服迷彩裤子_李宁运动裤男长裤冬加绒加厚休闲纯棉收口跑步裤正品小脚宽松卫裤_鲁美南韩丝运动裤女春秋高腰长裤中老年运动裤女夏薄款 直筒_安踏运动裤男长裤2018秋冬新款休闲修身小脚收口跑步加绒男裤卫裤_安踏运动裤男士针织长裤2018秋季新款休闲裤官方正品棉训练裤子_安踏运动裤男装秋季宽松直筒2018新薄款春大码黑色针织休闲长裤子_安踏女裤2018秋冬加绒小脚宽松长裤显瘦运动裤女收口长裤休闲裤女_安踏运动裤男长裤2018秋季新款正品小脚收口学生保暖加绒裤子男_安踏运动裤女长裤2018秋季新品运动长裤修身收口女运动裤休闲长裤_安踏运动裤长裤男装2018秋季收口修身小脚裤冬季休闲跑步裤男裤子_安踏运动裤男士加绒长裤2018冬季新款正品修身保暖舒适收脚健身裤_安踏运动裤加绒男长裤2018秋冬新款修身收口小脚保暖加厚棉跑步裤_安踏男裤运动裤薄款夏2018春秋季新款长裤收口小脚卫裤男束脚裤子_安踏运动裤男长裤2018新款秋季针织休闲裤直筒官方正品薄款裤子_安踏运动裤男长裤2018秋季新款休闲棉跑步裤品牌正品舒适直筒卫裤_安踏女运动裤2018秋季新款长裤加绒保暖针织裤休闲舒适直筒运动裤_安踏长裤女运动裤2018新款休闲裤官方正品秋季时尚针织棉透气裤子_安踏运动裤男2018秋季新款长裤加绒加厚小脚裤保暖收口休闲裤子_安踏女士运动裤2018冬季新款正品女加绒保暖修身针织长裤16647742_安踏男运动裤当季新品KT汤普森系列加绒保暖拉链收口运动卫裤男裤_男女同款运动裤秋季修身九分裤男小脚条纹学生班服潮流休闲裤子_秋季装运动裤男士小脚卫裤子青少年休闲长裤束脚学生班服迷彩裤子_李宁运动裤男长裤冬加绒加厚休闲纯棉收口跑步裤正品小脚宽松卫裤_鲁美南韩丝运动裤女春秋高腰长裤中老年运动裤女夏薄款 直筒_安踏运动裤男长裤2018秋冬新款休闲修身小脚收口跑步加绒男裤卫裤_安踏运动裤男士针织长裤2018秋季新款休闲裤官方正品棉训练裤子_安踏运动裤男装秋季宽松直筒2018新薄款春大码黑色针织休闲长裤子_安踏女裤2018秋冬加绒小脚宽松长裤显瘦运动裤女收口长裤休闲裤女_安踏运动裤男长裤2018秋季新款正品小脚收口学生保暖加绒裤子男_安踏运动裤女长裤2018秋季新品运动长裤修身收口女运动裤休闲长裤_安踏运动裤长裤男装2018秋季收口修身小脚裤冬季休闲跑步裤男裤子_安踏运动裤男士加绒长裤2018冬季新款正品修身保暖舒适收脚健身裤_安踏运动裤加绒男长裤2018秋冬新款修身收口小脚保暖加厚棉跑步裤_安踏男裤运动裤薄款夏2018春秋季新款长裤收口小脚卫裤男束脚裤子_安踏运动裤男长裤2018新款秋季针织休闲裤直筒官方正品薄款裤子_安踏运动裤男长裤2018秋季新款休闲棉跑步裤品牌正品舒适直筒卫裤_安踏女运动裤2018秋季新款长裤加绒保暖针织裤休闲舒适直筒运动裤_安踏长裤女运动裤2018新款休闲裤官方正品秋季时尚针织棉透气裤子_安踏运动裤男2018秋季新款长裤加绒加厚小脚裤保暖收口休闲裤子_安踏女士运动裤2018冬季新款正品女加绒保暖修身针织长裤16647742_安踏男运动裤当季新品KT汤普森系列加绒保暖拉链收口运动卫裤男裤_秋冬季运动裤男长裤加绒加厚直筒宽松棉跑步大码收口春秋休闲卫裤_安踏长裤女士运动裤加绒保暖秋冬季2018新款正品女修身针织棉长裤_安踏运动裤男秋冬款长裤2018新款正品休闲卫裤直筒宽松加绒长裤男_安踏运动裤女长裤2018秋季新款休闲裤官方正品针织裤子黑色棉长裤_",
  "格力": "Gree/格力KFR-35GW/(35532)FNhCb-A1润慧空调一级变频WIFI大1.5P_格力干衣机烘干机家用速干衣柜架宝宝衣服烘干器小型烘衣机风干机_格力电暖气油汀取暖器家用节能速热省电暖器电热暖风机烤火炉油丁_格力取暖器小太阳家用电暖气节能宿舍办公学生取暖风机浴室烤暖炉_格力取暖器遥控壁挂式暖风机家用节能速热浴室防水冷暖热风电暖气_格力取暖器家用办公省电暖气片节能速热烤火炉防烫电热膜电暖气_格力电暖器浴居两用欧式快热炉立式防水速热电暖气节能省电取暖器_格力电暖气家用摇头冷暖两用暖风机速热节能小太阳静音立式取暖器_格力小太阳取暖器家用办公室节能省电迷你电暖气机宿舍台式烤火炉_格力电暖气取暖器小型家用节能省电静音速热非电油汀暖风机烤火炉_格力取暖器家用浴室婴儿卫生间壁挂式居浴两用省电防水速热暖风机_格力碳纤维电暖器家用节能速热远红外电暖气立式摇头取暖器电热扇_格力壁挂式暖风机家用浴室防水电暖气冷暖热风电取暖器NBFC-X6021_格力电暖器 13片电热油汀取暖器干衣加湿智能恒温加热快2018新品_格力干衣机烘干机家用速干衣多功能省电小型除螨杀菌烤衣服烘干器_格力油汀取暖器家用节能省电电暖气13片电油丁暖风机烤火炉电暖器_格力电暖器家用节能壁挂式取暖器冷暖两用浴室防水速热暖风机暖气_格力取暖器13片电热油汀家用办公节能省电静音电暖器电暖气电暖炉_格力取暖器小太阳家用电暖器小型电暖气办公室学生电暖炉烤火炉_格力取暖器暖风机家用台式静音立式摇头迷你办公浴室小太阳电暖气_格力取暖器家用办公暖风机台式壁挂两用电热风速热宝宝洗澡电暖气_格力暖风机家用浴室取暖器防水速热可壁挂电暖器安全节能冷暖两用_格力取暖器家用电暖气片节能省电速热电热膜卧室遥控电暖器烤火炉_格力取暖器家用节能电暖气片省电电暖器速热烤火炉硅晶电热膜静音_格力暖脚器取暖器家用防烫办公室电暖器保健暖足器按摩取暖器_格力取暖器电热膜家用静音办公电暖气节能速热硅晶电热膜电暖器_格力小太阳电暖器J-8迷你家用取暖器节能办公远红外电暖气_格力取暖器油汀家用节能静音省电暖气11片油丁烤火炉干衣电热暖器_格力大松电暖气立式节能速热取暖器时尚摇头浴室省电家用暖风机_",
  "可优比": "可优比婴儿床围春夏秋宝宝床上用品儿童全棉防撞三件套透气可拆洗_可优比吸管杯宝宝保温杯儿童水杯防摔婴儿学饮杯幼儿园水壶两用_可优比儿童餐具套装婴儿碗勺辅食碗宝宝吃饭吸盘碗防摔注水保温碗_可优比儿童筷子训练筷宝宝练习筷学习筷家用小孩辅助筷学筷子男孩_可优比恒温调奶器智能全自动冲奶机泡奶粉婴儿玻璃热水壶温奶器_KUB可优比婴儿小棉被宝宝被子纯棉天丝春秋儿童幼儿园被四季通用_可优比防走失带牵引绳宝宝防丢失带手环儿童安全防走丢小孩防丢绳_可优比婴儿枕头1-3-10宝宝定型枕幼儿园儿童防偏头透气秋冬棉四季_KUB可优比婴儿床围彩棉可拆洗春夏季透气宝宝床上用品儿童三件套_可优比儿童玩具收纳架子置物架 多层储物柜幼儿园宝宝书架大容量_可优比宝宝学饮杯1-3岁防漏防呛婴儿吸管杯带手柄儿童防摔水杯_KUB可优比婴儿小被子儿童纯棉冬季宝宝纱布棉被幼儿园被四季通用_可优比幼儿园床品套件婴儿床上用品纯棉绿色儿童被子三件套全棉夏_可优比儿童书架宝宝简易小书架置物架幼儿园图书架塑料卡通绘本架_可优比抽屉式收纳柜子儿童玩具架子置物多层宝宝储物箱塑料整理柜_可优比婴儿床上用品婴儿床床围儿童防撞围栏宝宝床围秋冬全棉床品_可优比儿童书架绘本架宝宝玩具收纳架子幼儿园储物柜子塑料整理架_可优比宝宝餐椅子吃饭可折叠便携式婴儿餐桌椅座椅多功能儿童餐椅_可优比儿童吸管杯水杯幼儿园宝宝学饮杯婴儿防漏防呛6-18个月喝水_可优比婴儿冲奶机泡奶粉全自动智能恒温调奶器宝宝热水壶自动保温_可优比宝宝保温杯婴儿吸管杯学饮杯儿童水杯带吸管便携316保温杯_KUB可优比婴儿床床围防撞床上用品裆布套件棉宝宝床护栏四季通用_KUB可优比婴儿被子纯棉纱布彩棉春秋儿童幼儿园被子套件四季通用_KUB可优比婴儿浴巾美棉纱布浴巾新生儿洗澡巾儿童宝宝毛巾被超柔_可优比多功能婴儿背带宝宝前抱式腰凳四季通用 婴儿坐凳腰凳_可优比婴儿手口专用湿巾 新生儿宝宝湿纸巾湿巾80抽带盖*12连包_可优比宝宝折叠浴桶大号新生儿童洗澡桶小孩婴儿洗澡浴盆超大坐躺_可优比儿童浴桶洗澡盆保温大号加厚可坐婴儿洗澡桶宝宝泡澡沐浴盆_可优比宝宝餐椅多功能婴儿吃饭餐桌椅儿童学习书桌座椅学坐椅椅子_",
  "三只松鼠": "【三只松鼠_乳酸菌小伴侣520gx2箱】营养早餐面包口袋蛋糕零食_【三只松鼠_坚果大礼包1823g】礼盒每日坚果零食组合混合装10袋装_新品【三只松鼠_虾夷扇贝108g】扇贝肉即食零食大连特产海鲜香辣_每日坚果30包750g零食大礼包三只松鼠混合果仁成人儿童孕妇礼盒装_每日坚果30包750g零食大礼包三只松鼠混合果仁成人儿童孕妇礼盒装_三只松鼠小方蛋糕750g抹茶夹心糕点心办公室早餐面包一斤半礼品装_生日大礼包一箱好吃的休闲生日良品铺子送零食三只松鼠女友组合装_三只松鼠儿童画板双面磁性支架式升降多功能宝宝涂鸦画架写字板_零食大礼包一箱好吃的休闲零食良品铺子送女友三只松鼠生日组合装_零食大礼包一箱好吃的休闲零食良品铺子送女友三只松鼠生日组合装_零食大礼包一箱好吃的休闲零食良品铺子送女友三只松鼠生日组合装_零食大礼包一箱好吃的休闲零食良品铺子送女友三只松鼠生日组合装_",
  "史密斯": "A．O．Smith/史密斯F160B AO电热水器家用速热储水式60l升短粗款_A．O．Smith/史密斯SCE-60B1电热水器无地线家用洗澡60升L储水ao_川久体育 Adidas Stan Smith 三叶草史密斯绿尾板鞋小白鞋M20324_Adidas三叶草Stan Smith史密斯绿尾蓝尾粉尾小白鞋休闲板鞋B24105_AO史密斯R50VTC1 厨房过滤家用净水器 专利反渗透滤芯直饮净水机_Adidas/三叶草 Stan Smith史密斯绿尾 休闲板鞋 M20324/M20605/_北卡adidas Stan Smith 烫金粉尾 绿尾 粉尾 蛇纹粉尾 金标贝壳头_阿迪达斯男鞋三叶草2018新款秋stan smith史密斯黑休闲板鞋m20327_Cspace Adidas Stan Smith 三叶草史密斯绿尾板鞋 M20605 M20324_A．O．Smith/史密斯F280保养电热水器家用洗澡80升L速热储水式AO_【EDC sports】亏本清仓Adidas stan smith 纯白尾史密斯S76330_adidas三叶草Stan Smith史密斯红绿蓝尾板鞋M20324 M20325 M20326_【阿绿】Adidas三叶草Stan Smith史密斯粉尾男女鞋低帮板鞋CP9702_AO史密斯R500MTD2 厨房过滤家用净水器 集成水路复合型净水机_阿迪达斯三叶草男鞋2018夏季新款史密斯蓝尾运动休闲板鞋AC8575_AO史密斯净水器机家用厨房自来水过滤直饮即滤反渗透UV抑菌400F1_AO史密斯家用厨房过滤净水器 R600ETD1 反渗透大流量直饮净水机_阿迪达斯男鞋2018秋季休闲鞋三叶草板鞋Smith史密斯小白鞋M20324_【金小姐】Adidas/阿迪达斯史密斯2018春新款情侣休闲鞋CQ2469_Super制造 Adidas Stan Smith 三叶草绿尾 情侣男女小白鞋 M20324_『Cspace』Adidas StanSmith史密斯三叶草咖啡色休闲板鞋 S75542_",
  "优衣库": "【现货】日本优衣库airism防晒衣女连帽凉感透气速干uv防晒服包邮_这是真防晒的优衣库防晒衣日本本土2018新款防紫外线束干不闷热_日本优衣库长袖夏防晒衣外套2018新款防紫外线透气薄款海外购正品_少现货！ 2018年日本女款优衣库透气 防晒服UV紫外线长袖带帽外套_2018新款日本采购优衣库防晒衣AIRISM皮肤衣CUT90%抗UV_日本原版正品UNIQLO优衣库哆啦A梦 村上隆蓝胖子玩偶公仔机器猫_优衣库防晒衣女日本2018新款防uv紫外线长袖带帽外套本土采购日版_日本原版正品uniqlo优衣库哆啦a梦村上隆蓝胖子玩偶公仔毛绒玩具_日本正品uniqlo优衣库村上隆哆啦A梦机器猫公仔玩偶叮当猫蓝胖子_日本uniqlo优衣库doraemon机器猫村上隆蓝胖子玩偶公仔毛绒玩具_日本uniqlo优衣库doraemon叮当猫村上隆蓝胖子玩偶公仔毛绒玩具_日本uniqlo优衣库doraemon哆啦a梦村上隆蓝胖子玩偶公仔毛绒玩具_原版日本正品UNIQLO优衣库哆啦A梦村上隆机器猫公仔蓝胖子 现货_哆啦A梦公仔村上隆优衣库太阳花机器猫小叮当玩偶蓝胖子娃娃玩具_(现货)日本正品采购优衣库村上隆涂鸦哆啦A梦机器猫公仔娃娃玩偶_UNIQLO x KAWS  SNOOPY 史努比 毛毛公仔_",
  "三星": "纽曼 N5300移动滑盖老人手机男女超长待机大屏大字大声推盖推拉经典怀旧老款备用机全新正品三星诺基亚老人机_✅索爱 SA-T618C正品移动电信版天翼按键直板老人手机超长待机男女学生大屏大字大声老年手机三星诺基亚老人机_索爱 SA-Z6翻盖老人机超长待机大屏大字大声移动电信版老年手机男女款学生诺基亚三星老年机按键备用机_Samsung/三星MZ-76E250 860EVO 250G固态硬盘硬 笔记本台式机一体机SSD固态盘硬250g 兼容联想 华硕 惠普_Samsung/三星MZ-76E250B/CN 860EVO SSD笔记本台式机固态硬盘250G_Samsung/三星MZ-76E250 860EVO 250G SSD SATA接口台式机 笔记本通用 SSD固态硬盘 固态硬固盘_【分期免息】Samsung/三星MZ-76E500 860EVO 500G SSD笔记本台式机固态硬盘 固态硬固盘硬盘固态ssd硬盘固态_Samsung/三星MZ-76E500B/CN 860EVO 500G SSD笔记本固态硬盘_Samsung/三星MZ-76E250 860EVO 250G 台式机 笔记本固态硬盘SSD电脑固态盘硬250gb 硬固盘固态硬250g_Samsung/三星MZ-76E500 860EVO 500G  固态硬盘 笔记本台式机SSD 固态硬固盘 固态盘硬 500g_三星860EVO 500g 固态硬盘 ssd硬固 固态盘 笔记本台式 一体机电脑通用 sata接口 兼容联想 华硕 惠普_Samsung/三星SM-T350 Galaxy Tab A WLAN 16GB 8英寸 平板电脑_Samsung/三星MZ-V7E250BW 970Evo 250G SSD NVME M.2固态硬盘_Samsung/三星MZ-7LN120BW 笔记本台式机120g固态硬盘ssd非850evo_三星原装S9五代无线立式快速充电器S8/S8+/S7座充NOTE8苹果X快充_Samsung/三星MZ-V7E250BW 970EVO 250G m2固态硬盘SSD NVME M.2_Samsung/三星UA55MUF30ZJXXZ 55英寸4K智能网络平板液晶电视机_Samsung/三星固态硬盘860EVO 500G 笔记本SSD固态硬500g固态硬盘_Samsung/三星SM-T719C 8英寸 32GB全网通4G手机通话平板电脑安卓_宝仕利三星note9钢化膜全屏曲面全覆盖玻璃全胶吸附手机膜n9600弧边护眼抗蓝光防爆防摔水凝高清防指纹无白边_㊣Samsung/三星MZ-M6E250 860evo 250G mSATA SSD固态硬盘 笔记本台式机 固态硬固盘250G 固态盘硬_Samsung/三星860EVO 250G/500G/1T SATA3 台机笔记本固态硬盘ssd_Samsung/三星MZ-V7E1T0BW 970EVO 1TB M.2固态硬盘SSD 1t NVME_宝仕利三星S9钢化膜全屏3D曲面全覆盖S9+Plus手机玻璃保护膜防爆弧边耐刮花防摔防指纹无白边透明galaxy超薄_",
  "海底捞": "海底捞火锅底料 醇香麻辣牛油火锅底料调味料150g*3包_包邮多省海底捞麻辣青椒火锅底料香料串串香冒菜5kg桶装餐饮装_海底捞火锅蘸料【香辣味】120g*10包  新品尝鲜含芝麻酱花生酱_海底捞火锅蘸料原味120g*10袋调味料 蘸料原味_海底捞番茄火锅底料5kg火锅店餐饮装火锅调料商用大桶装酸香番茄_海底捞麻辣小龙虾调味料5kg饭店酒店餐饮装麻辣炒龙虾炒田螺调料_海底捞火锅 上汤酸菜鱼火锅底料调味料 老坛酸菜鱼调料360g_",
  "周黑鸭": "【周黑鸭品牌店_锁鲜】盒装卤鸭脖320g卤鸭锁骨240g鸭翅250gH_【周黑鸭旗舰店_锁鲜】气调盒装卤鸭脖320g卤鸭锁骨240g鸭翅250g_【周黑鸭旗舰店_锁鲜】气调盒装卤鸭脖200g卤鸭锁骨240g鸭翅250gH_【周黑鸭旗舰店_锁鲜】气调盒装卤鸭脖200g卤鸭锁骨240g鸭掌245g_【周黑鸭旗舰店_锁鲜】气调盒装卤鸭脖200g卤鸭翅250g卤鸭掌245g_【周黑鸭旗舰店】卤鸭脖140g鸭舌60g鸭翅145g 武汉特产零食品小吃_【周黑鸭旗舰店_锁鲜】卤鸭脖200gX1鸭锁骨240gX2盒 武汉零食小吃_周黑鸭品牌店_锁鲜鸭脖200g鸭锁骨240g鸭掌245g 武汉特产食品零食_【周黑鸭旗舰店_锁鲜】气调盒装卤鸭脖320g卤鸭锁骨240g鸭掌245g_【周黑鸭品牌店_锁鲜】气调盒装卤鸭肫鸭胗180gx2 武汉特产零食_周黑鸭品牌店_锁鲜卤鸭脖320g鸭锁骨240gx2盒 武汉特产食品零食_【周黑鸭品牌店_锁鲜】气调盒装卤鸭舌80gx2 武汉特产新鲜零食_【周黑鸭品牌店_锁鲜】气调盒装卤鸭舌80gx2 武汉特产新鲜零食H_",
  "创维": "✅Skyworth/创维32X6 32寸智能网络wifi液晶平板彩家用电视机 21_Skyworth/创维32X6 32英寸高清智能网络WIFI平板液晶电视机特价_✅Skyworth/创维43X6 43寸高清智能网络WIFI平板液晶电视机40 42_Skyworth/创维32X3 32英寸超薄液晶平板LED电视机 液晶电视42 43_Skyworth/创维40X6 40英寸高清智能网络WIFI平板液晶电视机42 39_✅Skyworth/创维43X6 43英寸液晶电视机42吋高清无线45智能家用_Skyworth/创维32X6 液晶 网络 智能 wifi 家用 电视机32英寸40_?Skyworth/创维32X6 32英寸高清智能网络WIFI液晶电视机家用42_Skyworth/创维43X6 43英寸高清智能网络WIFI平板液晶电视机45 42_Skyworth/创维32X6 32英寸高清智能网络WIFI液晶平板电视机4042_Skyworth/创维43X6 43英寸智能网络WIFI平板液晶官方电视机42_Skyworth/创维32X6 电视机32英寸网络智能wifi液晶电视机特价_Skyworth/创维32H5 32吋高清全面屏智能wifi网络平板液晶电视机_✅Skyworth/创维32X3 32英寸液晶电视机无线40高清LED节能家用X6_Skyworth/创维40X6 40英寸高清智能网络彩电液晶平板电视机42 43_Skyworth/创维32X3 32英寸高清超薄彩电液晶LED平板电视机特价_✅Skyworth/创维55H8M 官方授权55英寸4K高清电视机旗舰店同款_Skyworth/创维43X6 43英寸高清智能网络WIFI平板液晶电视机42_Skyworth/创维32X6寸高清智能网络WIFI平板液晶平板电视机39 40_Skyworth/创维75E8900 75G6D 75F7巨幕4色4K 大板智能超高清包邮_Skyworth/创维32X3 32英寸超薄高清平板LED电视机液晶电视40_Skyworth/创维50M9 50英寸4K超清智能语音WiFi平板液晶电视机55_Skyworth/创维40H5 40英寸智能高清网络全面屏平板液晶电视机32_Skyworth/创维43X6 43英寸高清智能网络WIFI平板液晶电视机42_Skyworth/创维55H5 55英寸4K超清智能网络全面屏平板液晶电视机_Skyworth/创维32X6 32寸电视高清智能网络WIFI液晶40寸40X6 43X6_✅Skyworth/创维43H5 43英寸4K高清智能网络液晶电视40家用42 55_Skyworth/创维43M9 43吋4K超高清智能网络液晶平板彩电视机40 42_Skyworth/创维58H7 58吋4K智能网络 无边框LED液晶电视机 60_",
  "耐克": "耐克男女装2018春季情侣款运动跑步卫衣圆领保暖套头衫857828-011_九千正品耐克MAGISTA鬼牌2ag钉中端人造草地足球鞋男844419-708_九千正品耐克MAGISTA鬼牌2代中端人造草碎钉TF足球鞋男844417-708_耐克2017冬季新款THERMA SPHERE ELEMENT男子长袖跑步上衣857828_扎吉体育Nike刺客11人工草AG男高帮足球鞋AH4041-401 AH4037-801_扎吉体育Nike BombaX TF男女儿童碎钉学生人工草足球鞋826488-414_九千正品耐克TIEMPO传奇6TF男牛皮人造草地碎钉足球鞋819216-001_九千正品耐克MERCURIAL刺客10中端男子碎钉TF足球鞋651646-580_NIKE/耐克2018夏季新款男子运动休闲透气舒适短袖POLO衫481961_九千正品NIKE耐克MERCURIAL刺客11人造草地AG足球鞋男831963-585_孤帆逐日耐克NIKEZOOM LIVE小托马斯男子篮球鞋 AH7567-101 003_扎吉体育Nike刺客Mercurial碎钉TF中端足球鞋831968-303-601-888_九千正品耐克Tiempo传奇6牛皮中端男人造草地AG足球鞋844399_NIKE耐克男子新款欧文运动休闲圆领长袖篮球T恤-AJ1976-100_耐克pro男子速干吸汗透气健身衣足球篮球跑步训练紧身运动长袖T恤_耐克男装切尔西18-19第二客场球衣足球运动比赛运动短袖919007_扎吉体育Nike Mercurial刺客TF高端碎钉足球鞋831975-301-606-888_九千正品耐克传奇6TF牛皮男童小学生碎钉儿童足球鞋819191-108_九千正品耐克Hypervenom毒蜂2人造草地男AG钉足球鞋844431-003_扎吉体育Nike Mercurial刺客TF碎钉人工草男足球鞋903614-616-801_九千正品耐克刺客11C罗高帮CR7人造草地ag钉足球鞋男AH4037-606_耐克女鞋2018秋季新款低帮轻便透气裂勾纹运动休闲板鞋AO2810-102_门店自提】Nike耐克短袖男2018秋新款运动服男装速干T恤891427_耐克男装上衣2017秋冬新款跑步训练运动套头长袖T恤857821-010_扎吉体育Nike Hypervenom TF毒蜂碎钉人工草足球鞋749899-003-108_九千正品耐克刺客11高端5人制小场人草碎钉TF足球鞋男831975-606_九千正品耐克Hypervenom毒蜂3tf人造草地碎钉足球鞋男852562-308_",
  "玉兰油": "Olay/玉兰油多效修护霜50g抗皱美白7重素颜面霜女旗舰店官网正品_Olay/玉兰油新生塑颜空气感凝霜50g 大红瓶空气霜 紧致清爽不油腻_Olay/玉兰油新生塑颜金纯面霜50g*2大红瓶紧致淡细纹滋润保湿面霜_谢娜玉兰油大红瓶空气霜50g正品OLAY新生塑颜空气感凝霜面霜only_玉兰油白里透红系列美白润肤霜50g送洗面奶+营养水保湿正品面霜_Olay/玉兰油新生塑颜金纯面霜50g大红瓶紧致面霜专柜旗舰店官网女_Olay玉兰油新生塑颜金纯面霜50g补水保湿滋润淡化细纹大红瓶_Olay/玉兰油多效焕颜活肤霜50g*2 补水保湿滋润 提拉紧致面霜女_Olay/玉兰油多效修护霜50g两瓶装补水保湿淡细纹美白女滋润面霜套_CQ美国发货OLAY玉兰油新生塑颜面霜抗皱补水保湿大红瓶48g*2瓶_玉兰油白里透红系列美白润肤霜+洁面+营养水补水保湿面霜正品套装_Olay/玉兰油新生塑颜金纯面霜50g补水保湿滋润 淡细纹紧致大红瓶_Olay/玉兰油细滑多效焕颜活肤霜50g*2瓶组合 补水保湿润肤面霜_Olay/玉兰油水漾动力盈润保湿露+深润保湿乳霜 滋润补水套装女_Olay/玉兰油新生塑颜金纯面霜50g 大红瓶滋润紧致保湿补水面霜_Olay/玉兰油多效焕颜活肤霜50g 补水保湿滋润 紧致淡细纹懒人面霜_【两只】玉兰油多效修护霜50g补水保湿提亮肤色面霜女素颜霜正品_玉兰油白里透红系列美白润肤霜50g*2祛斑素颜面霜官网旗舰店正品_",
  "荣耀": "2018新上市/分期免息/honor/荣耀畅玩7 全面屏智能手机全网通正品老年人机华为官方旗舰店学生大字大声大屏_速发 honor/荣耀体脂秤智能精准电子秤体重秤人脂肪减肥称_【新品现货】荣耀手环4Running版标准版OLED触控智能50米防水运动计步跑姿监测2两种佩戴长续航3_honor/荣耀正品耳机V10 9 V9 8 mate8华为mate10原装入耳式手机荣耀9i畅玩7X/C nova2s重低音旗舰店官网正品_荣耀穿墙宝无线电力猫一对家用路由器穿墙高速wifi智能适配扩展器_【当天发送臂包防刮贴膜荣耀手环4 0.95寸大彩屏50米防水心率泳姿睡眠监测蓝牙运动智能全屏触控智能通知通用_【新品】荣耀手环4智能Running版智能手表50米游泳防水运动计步跑姿监测长续航苹果安卓华为通用_新品荣耀路由2S 全千兆路由器无线5G家用wifi穿墙王高速端口双千兆200M光仟智能双频无天线pro电信移动大功率_全新原装适用华为荣耀10 COL-AL10屏幕总成带框内外触摸显示液晶_华为P9Plus原装充电器type-c数据线荣耀8/畅享7X/麦芒6/Mate8/荣耀V9/Nova青春版手机nova3S正品快充插头_华为荣耀6plus原装屏幕总成带框手机液晶内外触摸显示玻璃屏全新_荣耀原装自拍杆通用型mate10手机P20 9直播苹果x小米补光拍照_【包邮】美逸华为honor/荣耀畅玩7X钢化膜全屏覆盖手机保护贴膜_华为荣耀V8/荣耀8原装屏幕总成带框 KNT/FRD内外屏显示触摸手机屏_【新品】荣耀手环4Running版 智能运动计步防水游泳表 跑姿睡眠多功能监测男女生通用新款华为原装_",
  "百雀羚": "百雀羚橄榄精华油1号护肤防干裂脸部补水保湿孕妇妊娠纹全身精油_百雀羚止痒润肤露身体乳保湿滋润香体乳补水去鸡皮全身干性肤质_百雀羚三生花护手霜滋润女保湿补水嫩肤不油腻防干裂四季通用秋冬_百雀羚橄榄油护肤护发脸部预防孕妇妊娠纹全身精油官方旗舰店官网_百雀羚草本 水嫩倍现护肤套装女 补水保湿控油化妆品套装 水乳 霜_正品百雀羚止痒润肤露保湿型200G男女秋冬全身防干燥身体乳润肤乳_✅百雀羚男士洗面奶控油送美白祛痘去黑头深层清洁官方旗舰店官网_百雀羚橄榄油护肤精油1号护发脸部补水预防孕妇妊娠纹全身按摩_百雀羚男士护肤品套装控油补水洗面奶套装保湿正品洗脸护肤套装_百雀羚止痒润肤露身体乳持久保湿滋润去鸡皮香体非美白全身补水女_百雀羚经典面霜24h小时保湿霜50g深度锁水保湿润肤霜素颜霜擦脸油_百雀羚男士面霜套装焕能醒肤修护霜秋学生冬季补水保湿控油护肤品_百雀羚洗面奶男控油保湿去黑头学生洁面乳男士官方旗舰店官网正品_",
  "五谷磨房": "五谷磨房提子燕麦片伴侣冲饮早餐代餐食品 即食水果谷物小袋装_五谷磨房芒果燕麦五谷伴侣燕麦片即食冲饮谷物营养早餐食品代餐_五谷磨房提子燕麦五谷伴侣早餐食品燕麦片即食水果谷物早餐麦片_五谷磨房椰子燕麦片伴侣营养早餐五谷杂粮芝麻袋装即食冲饮谷物_五谷磨房椰子燕麦片 五谷杂粮伴侣谷物袋装营养冲饮 即食粥早餐_五谷磨房芒果燕麦伴侣 五谷磨坊营养早餐燕麦片即食谷物冲饮代餐_五谷磨房坚果谷物燕麦片免煮即食营养混合坚果冲饮非脱脂早餐_五谷磨房红豆薏米芡实茶赤小豆薏仁去除茶湿茶大麦茶叶花茶组合_",
  "百草味": "【百草味-每日坚果750g/30袋】混合坚果大礼包组合休闲零食干果仁_百草味零食大礼包空投箱组合超大一整箱送女友小吃混合装空头网红_【百草味-香辣/五香牛肉粒100g*2袋】牛肉干休闲零食小吃_【百草味-仁仁果750g】每日坚果混合30包孕妇零食礼盒_百草味大礼包零食小吃组合装网红送男女生吃货休闲食品整箱混合装_【百草味-水果干礼盒1113g】芒果干菠萝干草莓山楂果脯零食蜜饯_百草味零食坚果大礼包干果散装组合混合装一整箱吃货休闲小吃食品_【百草味-夏威夷果200gx3袋】坚果零食干果 奶油味送开口器_【百草味-芒果干120gx5袋】休闲零食小吃蜜饯水果干类 特产食品_百草味零食大礼包组合小吃美食好吃休闲食品网红混合装散装一整箱_百草味10种水果干零食大礼包送女友生日礼物 芒果干果脯组合_百草味坚果组合598g 夏威夷果 碧根果 炭烧腰果 休闲零食品_",
  "大益": "大益金柑普 新会陈皮柑普茶 小青柑 110克 柑普洱熟茶_8592大益熟茶2018年1801批普洱茶叶饼茶357g克_大益普洱茶熟茶 2018年1801批8592饼茶 357克大益七子饼茶叶_大益普洱茶经典口粮茶7542生茶+经典7572熟茶 300克/套小饼茶叶_大益茶叶2018年经典普洱熟茶 50袋/盒 普洱茶袋泡茶  办公杯泡_大益普洱茶柠檬红茶 我爱你小青柑+喜欢你小青柠 85g*2 包邮_大益普洱茶熟茶迷你小沱茶36g*7盒组合茶叶 普洱沱茶 熟沱小金沱_大益茶叶 2017年 V93 沱茶 普洱茶熟茶 500克 勐海茶厂_6盒组合大益茶叶2018年 小金沱 熟36克*6盒 迷你小沱普洱茶熟茶_大益2010/2011/2012年大小龙柱圆茶饼普洱熟茶357克随机发货_大益普洱茶熟茶茶叶 小金沱迷你沱茶 便携快捷冲泡普洱茶36g*7盒_整袋装大益普洱茶沱茶2017年1701批V93熟沱茶100g*5沱_送1片 2盒组合大益普洱茶2014年1401批 琥珀方砖 熟茶8片*60克_大益茶云南普洱茶大益饼茶普洱茶熟茶7262 普洱特级饼茶茶叶茶饼_买2送1大益普洱茶 2017年1701批 7452 熟茶七子饼 357克勐海茶厂_大益茶叶 2018年 普洱茶 经典普洱生茶 袋泡茶 50袋/盒_云南大益普洱茶2017年经典7542生茶+经典7572熟茶300g/套小饼茶叶_普洱茶 熟茶饼经典标杆熟茶 老茶客推荐1701批7572大益150g茶叶饼_大益茶金柑普柑益贝小青柑罐装200克陈皮熟茶叶_【买一送一】大益茶叶2017年7592普洱茶熟茶357g云南七子饼茶1701_大益普洱茶熟茶 象山普饼 2015年授权专卖店正品云南普洱茶叶357g_大益普洱 经典普洱 熟50包散装 含茶酵素 袋泡茶熟茶90克_3盒组合大益茶 普洱茶 2012年 如意 沱茶 熟茶 100克*3大益茶叶_大益小青柑新会陈皮柑普茶110g桔普熟茶小甘橘普洱茶叶_买2份送25袋大益茶叶花茶玫瑰普洱熟茶散茶80gX2盒共100袋便携茶_大益普洱茶熟茶勐海茶厂普洱茶500g沱茶v93 17年1701批包邮_大益普洱茶标杆生熟茶经典组合2018年7572+1801批7542旺世版包邮_",
  "波司登": "波司登羽绒服中长款女中老年厚外套修身连帽款韩版保暖羽绒服潮_波司登2018新款秋冬季轻薄羽绒服女短款外套时尚韩版潮B80131006_波司登时尚简约修身短款舒适气质羽绒服女加厚保暖带毛领B1301180_波司登时尚羽绒服中老年女加厚修身貉子毛领连帽中长款_波司登中老年羽绒服女内胆秋冬妈妈装新款大码内穿羽绒服加厚内恤_2018新款秋冬波司登轻薄羽绒服女短款修身青年情侣时尚超薄款外套_波司登迪士尼女长款时尚毛领保暖冬季连帽韩版个性羽绒服B1601136_波司登中老年羽绒服女短款轻薄韩版宽松轻便鸭绒外套秋B80131010B_波司登女短款时尚运动休闲印花羽绒服韩版连帽青年学生冬装外套潮_波司登轻薄羽绒服女短款 秋冬韩版修身户外运动休闲立领保暖外套_波司登气质女士双排扣毛领中长款修身连帽显瘦羽绒服B1301288S_波司登新款加肥妈妈装中老年大码女短款加厚羽绒服正品b1601336b_波司登轻薄羽绒服女短款连帽新款修身时尚休闲显瘦韩版B70131002_波司登春秋季短款时尚韩版修身潮轻薄冬季羽绒服女式外套B1701522_波司登羽绒马甲女内胆中老年款加厚保暖背心马夹秋冬坎肩妈妈装_波司登超轻薄羽绒服女短款2018秋冬新款连帽蓄热宽松大码轻便时尚_波司登羽绒服女款 短款 时尚轻薄修身潮外套正品秋羽绒B1401030_波司登羽绒服女士大众气质百搭收腰保暖中长款毛领外套 B1301238_波司登女羽绒服冬季甜美时尚连帽修身加厚保暖女短款B1401130_波司登新款羽绒服冬季大毛领宽松韩版加厚保暖修身外套女中长款_波司登冬保暖中长款收腰修身女狐狸毛纯色时尚女式羽绒服B1601246_波司登2018新款冬加肥加大内胆中老年大码羽绒服女内恤B1701610B_波司登羽绒马甲女外套韩版冬季女式外穿轻薄款鸭绒背心B80131002_波司登羽绒服女中长款韩版轻薄正品超立领潮秋冬薄款2017新款修身_波司登羽绒服新款加肥加大码中老年妈妈宽松保暖加厚冬外套女短款_波司登轻薄羽绒服女短款连帽2018新款加肥加大码中老年B80131012B_波司登羽绒服女中长款 冬季时尚大毛领中老年加厚保暖妈妈款_波司登春秋季中长款立领时尚轻薄羽绒服女气质立领简约B70131104_波司登羽绒服正品女士加肥加厚加大码妈妈中老年宽松保暖短款_",
  "华为": "2018新上市/分期免息/honor/荣耀 畅玩7 全面屏智能手机全网通正品老年人机华为官方旗舰店学生大字大声大屏_直降200】现货荣耀6a honor/荣耀 畅玩6A全网通华为手机智能7C_Huawei/华为畅享8e青春华为智能老人手机全网老年机大屏大字大声_Huawei/华为畅享8e全网老年智能手机大屏大字大声超长待机老人机_免息减20元送豪礼Huawei/华为畅享7 Plus 高配官方旗舰店手机正品5.5英畅想7s千元学生价畅享8官网降价plus_分期送蓝牙耳机 Huawei/华为畅享7s全网通智能正品手机畅想7plus_分期送蓝牙耳机 Huawei/华为nova 3e全网通4G全面屏官方正品手机_",
  "小米手机": "小米生态链 21KE/21克 MC001S触屏老人手机智能老人机超长待机大_☑小米生态链21KE F1/21克老人手机移动超长待机直板按键男女老人机大声大字军工三防学生迷你备用诺基亚手机_小米生态链21KE C1 21克正品直板按键移动大字大声老人手机超长待机老人机军工三防学生儿童备用诺基亚手机_乐呵呵原装红米note2电池1S正品2A手机note小米2S BM20 44 42 45大容量lehehe原装官网增强版全新电板bm41 40_乐呵呵原装小米5电池note3大容量6 5s米4C NOTE4x顶配版max2红米pro正品note5a mix2s 5splus手机4A 4S 4x 3s_小米8手机壳软硅胶8SE外壳小米6全包边MI8防摔创意保护套MI6微磨砂男女款个性黑红色简约卡通潮新款_",
  "卫衣": "秋季情侣运动卫衣男女同款卫衣运动休闲连帽针织套头衫男圆领卫衣_重磅尖货！时尚bo主、明xing都爱穿！加薄绒宽松长袖连帽卫衣秋冬_春秋款男士情侣装ins连帽加绒卫衣男装潮流韩版秋装宽松套装外套_2018秋冬新款保暖外套休闲时尚加厚外衣中年修身加绒卫衣女中长款_法国订单秋冬季 休闲运动风纯棉加绒宽松连帽长袖套衫女卫衣/绒衫_豹纹高领套头毛茸茸港味复古chic宽松加厚加绒卫衣2018新款女冬季_champion潮牌冠军正品男女同款圆领卫衣情侣休闲运动百搭外套帽衫_缪可秋冬装女2018新款字母印花牛仔拼接长袖连帽卫衣休闲宽松上衣_缪可冬装女2018新款字母印花拼接长袖连帽卫衣假两件休闲时尚上衣_INFLATION|原创潮牌秋冬装欧美街头撞色宽松掉肩加绒男式连帽卫衣_素品 复古文艺长袖连帽卫衣2018秋冬新款中长款百搭休闲加绒外套_韩国东大门18秋冬时尚开叉袖口小心机运动衫印花蕾丝拼接套头卫衣_纤雅芙长袖卫衣女春秋装韩版大码宽松百搭套头圆领打底t恤卫衣棉_韩国东大门2018秋冬新款DAI卡通字母时尚圆领长袖宽松套头卫衣女_设计很独特上身确实不错 半高圆领简约纯色显瘦落肩袖抗起球卫衣_吉普盾秋装男士新款韩版青少年长袖t恤学生日系上衣打底衫卫衣潮_NH奈社 必入基础款！初冬新品 半高领字母绣花超厚加绒套头卫衣_连帽加绒卫衣开衫女宽松休闲外衣加厚显瘦长袖韩版冬季拉链外套潮_时尚简约 18年春款 纯色字母抽带 前短后长开叉连帽卫衣女_南极人男装男士长袖t恤加绒青年韩版连帽卫衣潮流秋冬2018新款_加绒卫衣女士中长款2018秋冬新款休闲时尚加厚外衣中年人保暖外套_春秋款男士加绒ins连帽卫衣男装情侣装宽松学生秋装韩版潮流外套_怪兽的衣柜2018秋冬宽松长袖T恤女卡字母卡通印花抽绳宽松卫衣女_法国 秋冬 高阶品质减龄时尚保暖加绒加厚休闲运动外套连帽卫衣女_",
  "长虹": "Changhong/长虹32D3F 32吋彩电智能网络WIFI液晶电视机特价21 39_Changhong/长虹32D3F 32英寸智能网络电视机32吋液晶电视机家用_Changhong/长虹32D3F 32英寸液晶电视机智能网络WIFI卧室彩电24_Changhong/长虹43D3S 43吋液晶电视机4K高清网络智能wifi平板 40_Changhong/长虹49A3U 49吋4k超高清智能网络平板液晶电视机50 55_Changhong/长虹32T8S 欧宝丽32英寸网络智能wifi彩电液晶电视机_Changhong/长虹55A3U 55英寸4K超清智能网络平板液晶电视机60_32英寸小彩电高清液晶电视机32M1 Changhong/长虹官方旗舰店21 39_特价32英寸网络智能wifi液晶电视机40Changhong/长虹32T8S欧宝丽_Changhong/长虹32T8S 欧宝丽智能网络彩电平板液晶电视机32英寸_Changhong/长虹32D3F 32英寸64位24核智能网络LED平板液晶电视机_Changhong/长虹43D3F 43英寸智能网络LED平板液晶电视机45_Changhong/长虹43T8S 43吋智能网络WIFI平板液晶电视机欧宝丽 45_长虹39D3F 39英寸液晶电视机网络智能wifi彩电官方旗舰店32 40 43_Changhong/长虹32D3F 32英寸网络wifi智能电视LED液晶平板电视机_Changhong/长虹39M1 39英寸蓝光节能LED彩电平板电视液晶电视40_Changhong/长虹60D3P 60吋32核4K智能 HDR平板液晶LED电视机_Changhong/长虹32T8S 欧宝丽32英寸网络wifi智能LED小液晶电视机_Changhong/长虹32M1 32吋高清led液晶屏卧室平板电视机39 24 26_Changhong/长虹43D3F 43英寸网络智能wifi液晶电视机39 40 50 55_Changhong/长虹32M1 32英寸蓝光节能LED彩电平板电视液晶电视24_Changhong/长虹43m1 43吋彩电蓝光护眼高清平板led液晶电视机40_Changhong/长虹43m1 43英寸全高清液晶电视LED节能平板电视机42_?Changhong/长虹43D3F 43英寸WIFI智能网络平板液晶电视机卧室_Changhong/长虹32T8S 欧宝丽32吋64位智能网络LED平板液晶电视机_Changhong/长虹43T8S欧宝丽43英寸液晶电视机智能wifi网络彩电42_✅✅49吋英寸LED智能4K网络平板液晶电视机Changhong/长虹49A3U_Changhong/长虹32T8S 欧宝丽32吋64位智能网络LED平板液晶电视机_Changhong/长虹43D3F 43英寸64位24核智能网络LED平板液晶电视机_",
  "预留1": "1",
  "裂帛": "裂帛2018秋季新款气质立领刺绣中长款捏褶水洗牛仔外套女士风衣_裂帛民族风2018秋装新款连帽刺绣韩版显瘦长袖百搭罗纹休闲卫衣女_裂帛女装长款长袖T恤2018秋装新款一字领刺绣修身显瘦打底衫女_裂帛2018秋季新款时尚翻领文艺刺绣深色系帅气个性全棉牛仔外套女_裂帛短袖T恤女2018夏季新款短款上衣纯棉打底刺绣修身显瘦_裂帛2018秋季新款抽绳套头连帽衫花朵刺绣宽松上衣外套长袖卫衣女_裂帛2018早秋新款连帽刺绣长袖个性抓绒上衣春装休闲酷潮女士卫衣_裂帛古风女装2018秋装新款民族风女上衣T恤短款修身长袖打底衫_裂帛卫衣2018秋装新款刺绣抽绳套头连帽衫溜肩刺绣长袖休闲女_裂帛2018秋季新款圆领刺绣少女休闲长袖上衣甜美套头打底衫卫衣女_裂帛2018秋季新款时尚圆领绣花休闲甜美风清新韩版学生长袖卫衣女_裂帛2018秋季新款时尚圆领绣花休闲甜美风清新韩版学生长袖卫衣女_裂帛民族风2018秋季新款女装打底衫短款T恤长袖上衣休闲卫衣宽松_裂帛2018冬装新款圆领刺绣落肩套头衫撞色宽松版毛衣女51171466_裂帛2018秋季新款圆领刺绣飞行员夹克水洗牛仔短款圆领外套上衣_裂帛2018夏装新款简约百搭圆领拼接文艺刺绣开襟长袖薄款针织衫女_裂帛休闲裤女2018秋季新款刺绣加绒长裤百搭宽松学生运动束脚裤子_裂帛2018秋季新款圆领露肩刺绣长袖显瘦装女士上衣休闲百搭卫衣女_裂帛2018秋季新款文艺甜美百搭圆领清新提花长袖女士外套针织开衫_裂帛女装2018秋新款圆领长袖修身显瘦上衣打底针织衫套头韩版毛衣_裂帛2018秋季新款圆领精美刺绣民族风浪漫蕾丝温柔舒适长袖T恤女_裂帛2018春装新款圆领印花上衣百搭针织打底衫长袖T恤女51170246_裂帛套头毛衣女2018秋季新款猫咪提花宽松长袖网红针织衫上衣潮_裂帛2018夏新款民族风文艺刺绣圆领上衣修身显瘦针织短袖T恤女装_裂帛旗舰店2018秋装新款长袖休闲卫衣外套薄百搭圆领刺绣女装上衣_",
  "点读笔": "RAZ-Kids英语分级读物Reading a-z英文彩色绘本支持小星星点读笔_起跑点中小学生点读笔课本同步教人版初中高中英语教材学习点读机_英语单词卡片幼儿启蒙中英文字母闪卡儿童早教教具点读笔有声小学_牛津阅读树第1+阶自然拼读30册 毛毛虫点读笔oxford reading tree_RAZ-Kids英语分级读物ReadingaaA-Z支持小星星小达人点读笔送音频_正品小星星点读笔支持RAZ A-Z分级阅读英语绘本点读版 含笔含书_步步高t2点读机点读笔t2点读笔原装正品原配件点读笔可充电_起跑点中小学生点读笔课本同步教人版语文数学英语学习机_步步高点读笔T800 步步高点读机点读笔T800-E原装正品包邮_好学子点读笔中小学生课本同步教人版英语教材初中高中点读学习机_小星星英语点读笔RAZ海尼曼牛津树分级点读版aa A-Z海尼曼送quiz_纽曼点读笔6-12岁儿童学习机幼小衔接认识字一年级学拼音点读机_彩虹兔自然拼读23册毛毛虫点读笔幼儿童英语启蒙早教材原版绘本_#凯迪克图书专营店 英国进口 英文原版绘本 usborne 彩虹兔自然拼读奇趣故事屋套装23册 支持好饿的毛毛虫点读笔_【支持小达人点读笔】麦克米伦 插图儿童字典词典 Macmillan English First Dictionary 科普百科认知童书 趣味理解词汇 英文原版_步步高点读机t2点读笔t2原装笔配件不含机器充电点读笔T2专用_RAZ-kids美国原版分级阅读绘本aa点读笔90本a-z级分册支持小达人_纽曼拼音点读机小学1-6年级学前班语文教材汉字笔顺笔画学习_人教pep新起点小学英语3三年级起点英语点读笔英语点读机_爱看屋点读笔早教机0-3-6岁婴幼儿童中英语益智玩具学习点读机_英语点读笔中小学生课本同步外语版教人版初中高中英语同步点读机_love English点读版、love phonics、新版love+ 专用点读笔_优珀中小学英语点读笔点读机课本同步人教外语版湘教鲁教上海陕旅江苏译林闽教福建教育教材学习爱仁英文书膜_",
  "飞利浦": "飞利浦电动剃须刀充电式荷兰三刀头全身水洗男士正品原装刮胡刀_飞利浦电动剃须刀充电式全身水洗男士刮胡刀飞利浦官方旗舰店正品_Philips/飞利浦电动剃须刀男士充电式刮胡刀3刀头S3110/06_飞利浦电动剃须刀S1010 S1020充电式男士刮胡刀全身水洗干湿双剃_飞利浦电动剃须刀全身水洗充电式男士刮胡刀官方旗舰店正品胡须刀_飞利浦电动剃须刀S1010 S1020充电式男士刮胡刀全身水洗干湿双剃_飞利浦电动剃须刀男士刮胡刀充电式胡须刀三头全身水洗原装正品_飞利浦电动剃须刀男士刮胡三刀头快速充式电全身水洗原装正品进口_飞利浦电动剃须刀充电式旋转式三刀头水洗刮胡刀干湿两用男士正品_Philips/飞利浦电动剃须刀AT610 男士刮胡刀 胡须刀充电式三刀头_飞利浦电动剃须刀HS198/199便携式USB充电式刮胡刀双刀头礼盒装_Philips/飞利浦电动剃须刀小T刀 男士刮胡刀胡须刀可水洗QP2520_飞利浦电动剃须刀S5070 S5420三头充电男士刮胡刀S5050 S5091升级_飞利浦电动剃须刀 S5082 充电式男士刮胡刀S5079全身水洗原装正品_飞利浦电动剃须刀PT722 充电式男士刮胡刀全身水洗胡须刀AT798_Philips/飞利浦男士剃须刀HS198 充电式电动刮胡刀HS199刀头水洗_飞利浦电动剃须刀S1010 三刀头全身水洗干湿双剃 充电式正品S1060_飞利浦剃须刀S5079电动刮胡刀充电式男士胡须刀刨官方旗舰店正品_Philips/飞利浦电动剃须刀AT600双刀头水洗男士充电式刮胡刀_飞利浦剃须刀S5079电动刮胡刀充电式男士胡须刀刨官方旗舰店正品_Philips/飞利浦剃须刀电动刮胡刀男士胡须刀充电式3刀头s5110/06_飞利浦电动剃须刀AT891修剪器水洗切剃浮动男士刮胡刀PT786升级版_飞利浦电动剃须刀男士刮胡刀充电式干湿胡须全身水洗原装正品S526_飞利浦电动剃须刀S5079 男士三刀头水洗充电刮胡刀S5351 S5080_Philips飞利浦电动剃须刀S1560男士充电式剃胡刀头水洗荷兰进口_飞利浦电动剃须刀AT891 双重切须干湿两用男士刮胡刀 PT786升级版_飞利浦剃须刀电动充电式三头全身水洗男士刮胡刀PT786原装正品_",
  "羽绒服": "轻薄羽绒服女短款超轻薄立领连帽轻便正品大码秋冬外套反季节清仓_轻薄羽绒服女短款立领轻便超轻冬2018新款小款超薄外套大码南极人_轻薄羽绒服女短款立领连帽时尚韩版修身薄款女款外套大码秋冬反季_红豆羽绒服冬女装加长超长过膝盖到小腿加厚白鸭绒修身加肥加大码_2018新款羽绒服女时尚韩版百搭轻薄短款修身显瘦连帽大码冬装外套_素品 2018冬装新款轻薄羽绒服女士中长款保暖白鸭绒大码羽绒外套_韩国版宽松显瘦羽绒服女装新款大码中长款加绒加厚冬装外套_欧美大牌茧型长款过膝羽绒服女黑色亮面加厚宽松白鸭绒保暖外套潮_2018反季清仓韩国中长款衬衫领轻薄款羽绒服女休闲时尚外套显瘦潮_反季清仓特价超轻薄款秋羽绒服女短款正品大码修身韩版妈妈装外套_日代工厂，2018秋冬新款 蓬松饱满~！面包服女装羽绒服90%白鸭绒_反季轻薄羽绒服女中长款2018新款潮超轻薄薄款轻便连帽格子外套_Lips性价比之wang！！又暖又软又轻儿童款银色羽绒服给娃娃们囤_2017冬季欧洲站女装新款大码加厚显瘦宽松蝙蝠袖中长款羽绒服欧美_轻薄羽绒服内胆女修身短款冬长袖大码内穿白鸭绒中老年加厚妈妈装_超轻便女装加肥加大码女士轻薄款羽绒服短款新款胖mm200斤特_两面穿羽绒服女轻薄短款白鸭绒外套大码时尚连帽双面穿薄款羽绒衣_天天特价清仓2017新款连帽超轻便轻薄款羽绒服女装冬装短款大码_韩国版东大门中长款羽绒服女大真毛领宽松加厚大码胖mm200斤显瘦_依雪羽2018新款中老年羽绒服女装修身中长款大码加厚中年妈妈外套_舒朗羽绒服女连帽毛领加厚收腰显瘦拼接白鸭绒中长款外套S2134H71_烟花烫SD2018冬装新品女装气质甜美修身带毛领中长羽绒服樱雪_2018新款正品修身显瘦加长款羽绒服女超长过膝加厚大码冬装外套潮_2018冬新款轻薄羽绒服女中长款时尚修身女装薄外套潮反季清仓正品_冬季中老年羽绒服女中长款妈妈装宽松大码加厚加肥加大白鸭绒外套_2018新款轻薄短款修身轻便羽绒服女连帽立领大码外套薄款冬季保暖_2018新款正品加长款羽绒服女超长过膝加厚大码修身外套超保暖冬装_",
  "飞科": "飞科剃须刀电动刮胡刀男士充电式正品胡须刀头智能刮胡子剃预刀_正品飞科男士剃须刀电动刮胡刀智能充电式三刀头剃胡须子刀FS372_飞科男士车载剃须刀电动智能充电式胡须刀刮胡刀全身水洗剃胡子刀_飞科剃须刀男全身水洗充电式剃须刀电动刮胡刀胡须刀剃须刀FS873_飞科电动剃须刀男士充电式剃须刀水洗防水电动刮胡刀胡须刀_飞科剃须刀电动男士刮胡刀刀头水洗智能充电式胡须刀正品刮胡子刀_飞科剃须刀电动刮胡刀全身水洗充电式男剃剔胡须刀智能子正品车载_飞科男士车载剃须刀电动智能充电式刮胡刀全身水洗剃胡须子刀正品_飞科剃须刀男正品三刀头电动剃须刀电动刮胡刀充电式胡须刀剃须刀_飞科剃须刀电动男士刮胡刀全身水洗智能充电式胡须刀正品FS373_飞科剃须刀电动男士刮胡刀智能充电式家用剃胡子刀正品2头修剪器_飞科男士剃须刀电动胡须刀充电式2头便携式刮胡刀旗舰店官方正品_飞科男士剃须刀电动胡须刀正品充电式fs373全身水洗智能S刮胡刀_飞科剃须刀男士智能全身水洗胡须刀充电式电动刮胡刀正品刮胡子刀_原装正品飞科男士剃须刀电动刮胡刀智能充电式三刀头剃胡须刀水洗_飞科电动剃须刀男士充电式刮胡刀全身水洗智能胡须刀正品刮胡子刀_飞科剃须刀电动刮胡刀男胡须刀充电式便捷式迷你剃须刀FS711正品_飞科剃须刀男士电动刮胡刀胡子刀充电式防水胡须刀智能全身水洗_Flyco/飞科剃须刀电动飞科剃须刀男充电式刮胡刀男士胡须刀FS829_飞科电动剃须刀FS360充电式便携刮胡刀男士剃胡须刀电动须刨_飞科剃须刀电动刮胡刀男士官方充电式胡须刀智能刮胡刀旗舰店正品_飞科剃须刀电动刮胡刀男士充电式正品胡须刀头智能刮胡子剃预刀_正品飞科男士剃须刀电动刮胡刀智能充电式三刀头剃胡须子刀FS372_飞科男士车载剃须刀电动智能充电式胡须刀刮胡刀全身水洗剃胡子刀_飞科剃须刀男全身水洗充电式剃须刀电动刮胡刀胡须刀剃须刀FS873_飞科电动剃须刀男士充电式剃须刀水洗防水电动刮胡刀胡须刀_飞科剃须刀电动男士刮胡刀刀头水洗智能充电式胡须刀正品刮胡子刀_飞科剃须刀电动刮胡刀全身水洗充电式男剃剔胡须刀智能子正品车载_飞科男士车载剃须刀电动智能充电式刮胡刀全身水洗剃胡须子刀正品_飞科剃须刀男正品三刀头电动剃须刀电动刮胡刀充电式胡须刀剃须刀_飞科剃须刀电动男士刮胡刀全身水洗智能充电式胡须刀正品FS373_飞科剃须刀电动男士刮胡刀智能充电式家用剃胡子刀正品2头修剪器_飞科男士剃须刀电动胡须刀充电式2头便携式刮胡刀旗舰店官方正品_飞科男士剃须刀电动胡须刀正品充电式fs373全身水洗智能S刮胡刀_飞科剃须刀男士智能全身水洗胡须刀充电式电动刮胡刀正品刮胡子刀_原装正品飞科男士剃须刀电动刮胡刀智能充电式三刀头剃胡须刀水洗_飞科电动剃须刀男士充电式刮胡刀全身水洗智能胡须刀正品刮胡子刀_飞科剃须刀电动刮胡刀男胡须刀充电式便捷式迷你剃须刀FS711正品_飞科剃须刀男士电动刮胡刀胡子刀充电式防水胡须刀智能全身水洗_Flyco/飞科剃须刀电动飞科剃须刀男充电式刮胡刀男士胡须刀FS829_飞科电动剃须刀FS360充电式便携刮胡刀男士剃胡须刀电动须刨_飞科剃须刀电动刮胡刀男士官方充电式胡须刀智能刮胡刀旗舰店正品_飞科剃须刀电动男士刮胡刀全身水洗智能充电式剃胡子刀正品FS373_飞科剃须刀电动FS362男士刮胡刀智能充电式三刀头防水胡须刀正品_飞科剃须刀全身水洗剃须刀电动智能男刮胡刀充电式胡须刀飞科正品_",
  "贝亲": "【贝亲官方旗舰店】婴儿湿巾柔湿巾100片装 6连包*4组 PL347*4_贝亲彩绘宽口径ppsu奶瓶240ml婴儿耐摔带吸管手柄官方旗舰店正品_贝亲婴儿润肤霜滋润宝宝面霜润肤乳35g儿童秋冬护肤品正品护肤霜_【贝亲官方旗舰店】玻璃宽口径奶瓶新生儿婴儿硅胶奶嘴奶瓶套装_贝亲尿布桶 婴儿尿片纸尿裤尿不湿处理桶宝宝垃圾桶除味桶收纳桶_贝亲宽口径玻璃奶瓶新生婴儿宝宝防胀气防摔带手柄吸管160/240ml_贝亲彩绘宽口径ppsu奶瓶婴儿耐摔手柄官方旗舰店正品330ml_贝亲婴儿宽口径彩绘ppsu奶瓶新生儿宝宝喝奶耐摔双手柄奶瓶240ml_日本原装进口贝亲婴儿指甲剪宝宝指剪刀新生儿防夹肉安全指甲钳_贝亲PPSU奶瓶宽口径新生儿奶瓶婴儿宝宝塑料奶瓶吸管240可配手柄_【贝亲官方旗舰店】迪士尼维尼熊系列洗发水润肤油 洗浴护肤组合_日本正品进口贝亲Pigeon宝宝专用手握式口腔训练牙胶 3个月以上_【贝亲官方旗舰店】婴儿湿巾手口专用70片装 6连包*4组 PL192*4_【贝亲官方旗舰店】奶瓶奶嘴套装清洗套装 奶瓶刷 奶瓶果蔬清洗剂_【贝亲官方旗舰店】宽口径PPSU奶瓶奶嘴清洗剂套装+LL奶嘴+L奶嘴_贝亲纸尿裤婴儿干爽大码宝宝尿不湿XL码64片纸尿裤_日本贝亲婴儿沐浴润肤套装 沐浴露500ml+按摩油80ml+润肤乳120ml_贝亲婴儿宽口PPSU奶瓶套装160+240ML婴儿防胀气奶瓶宝宝塑料奶瓶_",
  "海尔": "Haier/海尔EC5U厨房5升小厨宝储水式小型速热家用电热水器热水宝_Haier/海尔EHF-T260(C)(CP速热水龙头家用厨宝)即热式电热水龙头_Haier/海尔EHF-T260(C)(CP)恒温加热电热水龙头即热式快速热厨宝_海尔电热水龙头即热式快速热加热自来水过水热小厨房宝热水器家用_Haier/海尔EHF-T260(C)(G)恒温即热式热水器厨房海尔电热水龙头_Haier/海尔RFC160MXSAVA(G)家用中央空调 一拖五 6匹 四室一厅_Haier/海尔EHF-TW260(C)(CP)恒温即热式电热水龙头卫生间下进水_海尔RFC100MXSAVA(G)中央空调 家用 一拖三 风管机 4匹变频包安装_Haier/海尔ZQD90F-12LCS 家用消毒柜嵌入式消毒柜高温消毒_Haier/海尔LE32A21J 32英寸高清液晶平板电视32寸电视机品牌新款_Haier/海尔RFC72DXSAVA家用中央空调 一拖二空调风管机变频大3匹_Haier/海尔EHF-T260(C)(CP)厨宝电热水龙头即热式快速热加热厨房_",
  "西门子": "西门子地插座全铜防水弹起式家用隐藏不锈钢五孔地面地板插座_西门子睿致系列开关插座面板家用电源睿智大板无框五孔10只套餐_西门子五孔地插全铜防水带防伪西门子地板插座送黑色暗盒_双十一预售五孔10只装西门子开关插座 睿致远景悦动品宜灵致灵动_西门子开关插座大面板皓睿砂釉金色86型五孔插座带开关40只套餐_西门子开关插座大面板皓睿硒釉银86型家用五孔开关带荧光40只套餐_西门子开关插座皓睿玉釉白86型五孔家用大面板开关带荧光40只套餐_西门子开关插座套餐悦动香槟金38只装86型家用五孔插座带开关_SIEMENS/西门子BE525LMS0W 嵌入式微波炉家用内嵌多功能烧烤玻璃_SIEMENS/西门子ER71237MP大火力防爆钢化玻璃家用嵌入式燃气灶具_SIEMENS/西门子WM12P2C99W 滚筒洗衣机9公斤家用全自动1200转变频_SIEMENS/西门子WD14U5600W 10公斤洗烘干一体全自动滚筒洗衣机_SIEMENS/西门子ER73F23EMP防爆玻璃大火力家用燃气灶灶具_SIEMENS/西门子950+71237吸油烟机燃气灶具套装自清洁烟灶套餐_SIEMENS/西门子436+525全新正品家用嵌入式洗碗机微波炉组合套装_SIEMENS/西门子WD14G4C91W 变频滚筒洗衣干衣机2017家用新品洗烘_SIEMENS/西门子HS363600W消毒柜嵌入式家用紫外线消毒碗柜镶嵌式_SIEMENS/西门子950+73F23E顶吸抽油烟机燃气灶套装自清洁烟灶套餐_SIEMENS/西门子WD14U5600W全自动家用滚筒智能变频10KG洗烘一体机_SIEMENS/西门子940+71237家用油烟机燃气灶套装自清洁烟灶套餐_",
  "伊利": "伊利纯牛奶250ml*24/箱 中粮我买网直供多仓发货_伊利纯牛奶250ml*24/箱  中粮我买网直供多仓发货_伊利谷粒多红谷苗条礼盒250ml*12/箱*2 中粮我买网直供多仓发货_包邮伊利安慕希 希腊风味酸奶 草莓味 205g*12盒*2提 新日期_伊利中老年奶粉营养高钙老人成人牛奶粉无蔗糖全脂罐装1000g_伊利中老年奶粉1000g*2罐男女士老人成人高钙营养牛奶粉冲饮送礼_伊利中老年高钙奶粉900g*2听礼盒装成人老年人营养早餐牛奶粉_伊利中老年多维高钙奶粉400g*4小袋装成人老人冲饮营养高钙牛奶粉_",
  "英氏": "英氏新生夹棉保暖和袍初生婴儿宝宝纯棉舒适上衣174866_英氏官方旗舰店新生儿秋冬夹棉和袍上衣0-1岁宝宝 174990_英氏女童长裤童装儿童灯芯绒裤女宝宝裤子 153180_英氏婴儿裤子 男女宝秋装秋裤纯棉休闲亲肤打底裤两件装 183B0349_英氏婴儿保暖上衣 男女宝秋冬夹棉保暖居家睡衣打底衫 189A7345_英氏女宝宝夹棉内衣秋冬儿童保暖加厚上衣单件174861 DM_英氏婴儿内衣 儿童秋冬夹棉内衣男女宝宝保暖上衣165451_英氏新生儿连体衣夹棉男宝连体哈衣秋冬保暖爬服144046_英氏女童牛仔裤中腰裤裤子休闲长裤儿童秋装裤子153182_英氏男女宝裤子儿童灯芯绒长裤 双面穿秋冬厚裤子153289_英氏官方旗舰店新生儿秋冬夹棉和袍上衣0-1岁宝宝  164188_英氏儿童保暖内衣加厚男女宝宝秋衣上衣单件两色144049_英氏儿童居家内衣 男女宝宝纯棉四季居家打底内衣单件 184A0948_英氏婴儿连体衣 宝宝夹棉连身衣哈衣加棉爬服174852 DM_英氏新生婴儿内衣男女宝宝纯棉系带和尚服系带和袍164083_英氏女童裤子秋冬中腰女宝宝长裤休闲裤153267_英氏新生儿和袍内衣 婴儿春秋贴身纯棉上衣 美国棉面料 174541_英氏婴儿衣服0-3岁宝宝纯棉上衣春秋儿童内衣两件装 183B0347_英氏新款婴儿秋衣儿童四季内衣 宝宝刺猬上衣174996_英氏儿童保暖上衣 中大童无袖居家衫 男女宝双面可穿背心189A7397_英氏婴儿内衣 儿童秋冬夹棉内衣男女宝宝保暖上衣 164768 164771_英氏秋冬装儿童保暖内衣男女宝宝夹棉秋衣婴儿上衣164770_英氏女童休闲裤 中腰纯棉春秋休闲裤 163237_英氏婴儿保暖裤 男女宝秋冬松紧腰夹棉长裤 儿童居家睡裤189A7347_英氏女童纯棉休闲T恤 翻领短袖套头上衣 184A0113_英氏婴儿内衣 男宝宝可爱白色纯棉保暖棉衣和服袍165459_英氏婴幼儿打底衫 新生儿男女宝宝秋冬加厚保暖套头内衣144050_英氏婴儿连体衣 儿童夹棉连帽保暖哈衣爬服 174858 DM_英氏女童卫衣 宝宝春秋夹棉套头卫衣 纯棉休闲童装衫 187A5169_",
  "美的": "Midea/美的F05-15A(S)小厨宝5升即热式家用热水器小型储水式_Midea/美的JSQ22-12HWA(T)天然气燃气热水器家用12升煤气液化气_Midea/美的F6.6-15A(S）小厨宝 即热式储水式热水宝热水器电家用_Midea/美的F05-15A(S)小型厨宝 厨房电热水器 上下即热式 储水式_Midea/美的Q216B燃气灶煤气灶天然气灶双灶家用炉灶台液化气灶具_Midea/美的F05-15A(S) 小厨宝厨房热水器速热即热储水式家用5L_Midea/美的F6.6-15A(S）小厨宝家用储水式厨宝即热热水宝速热6升_Midea/美的F05-15A(S)小型厨宝储水即热式 速热5L厨房热水器家用_美的抽油烟机装饰罩围板_Midea/美的JSQ20-G 天然气 燃气热水器家用电10升煤气液化气12L_Midea/美的F05-15A(S) 5升小型厨宝家用电热水器速热即热储水式_Midea/美的F05-15A(S)小型厨宝5升储水式家用厨房电热水器热水宝_美的Q216B/Q216燃气灶嵌入天然气煤气灶双灶家用台式液化气灶具_Midea/美的Q216 燃气灶煤气灶天然气灶液化气双灶炉台嵌入式家用_美的ZLP30T11消毒柜家用小型立式碗柜迷你台式消毒碗柜臭氧烘干康_美的油烟机DJ750R TJ8055 DJ570R DJ370R  DJ366R不锈钢装饰罩_Midea/美的F05-15A(S)厨宝小型储水即热式5升家用热水宝上下出水_Midea/美的F50-21WA1电热水器家用50升L卫生间速热小型洗澡机60_Midea/美的Q216B燃气灶煤气灶双灶家用天然气液化气灶具台嵌入式_Midea/美的F80-21WA1电热水器80升L家用卫生间速热洗澡节能正品_Midea/美的MQ4503-G燃气灶煤气灶液化气单灶嵌入式天然气单灶炉_Midea/美的MDVH-V100W/N1-5RO(E1)4匹一拖三中央空调全直流变频_Midea/美的F50-15WB5(Y) 电热水器50L家用遥控 储水式 速热50升_Midea/美的MG80V330WDX智能变频8公斤kg全自动家用滚筒洗衣机特价_嵌入式微波炉Midea/美的AG025QC7-NAH 内嵌式家用蒸立方蒸烤箱_Midea/美的MXV-ZLP100K03大容量家用消毒柜碗柜立式商用碗筷_",
  "苏泊尔": "苏泊尔电磁炉火锅家用智能正品学生电池炉灶特价炒菜官方旗舰店_苏泊尔电压力锅家用智能5L高压饭煲官方1特价2旗舰店3-4正品5-6人_苏泊尔豆浆机家用全自动智能小型破壁免过滤多功能官方旗舰店正品_苏泊尔电饼铛电饼档家用双面加热烙饼锅新款自动断电加深加大正品_苏泊尔绞肉机家用电动小型不锈钢多功能搅肉料理机剁辣椒碎菜打馅_苏泊尔养生壶家用玻璃电煮茶壶全自动加厚煮茶器多功能养身烧水壶_苏泊尔榨汁机家用全自动果蔬多功能水果小型迷你炸果汁辅食搅拌机_苏泊尔电火火锅锅家用多功能电炒蒸煮热菜锅插电一体锅2-3-4-6人_苏泊尔电蒸锅多功能家用自动断电大容量蒸笼商用蒸菜器官方旗舰店_苏泊尔电炖锅陶瓷电炖盅小熬煮粥锅紫砂锅煲汤神器家用1人2全自动_苏泊尔养生壶家用玻璃电全自动加厚煮茶壶煮茶器多功能养身烧水壶_苏泊尔电蒸锅多功能家用自动断电大容量蒸笼蒸菜器蒸汽官方旗舰店_苏泊尔电饭煲锅小迷你型家用官方智能6旗舰店5正品4全自动1-2-3人_苏泊尔电饼铛档家用新款双面加热烙饼锅煎薄饼机自动加深加大正品_苏泊尔榨汁机家用全自动果蔬渣分离多功能炸水果汁机迷你小型无渣_苏泊尔电热水壶官方旗舰店烧水壶家用304不锈钢自动断电保温水器_苏泊尔宝宝婴儿辅食料理机豆浆破壁打泥绞肉搅拌机多功能家用小型_苏泊尔榨汁机家用全自动果蔬渣分离多功能打炸水果扎汁机小型新款_苏泊尔电热水壶自动断电全自动家用烧水壶大容量304不锈钢正品_苏泊尔电压力锅家用智能5L高压饭煲1官方2特价3旗舰店4正品5人6-8_SUPOR/苏泊尔电炖锅家用全自动电炖盅煮粥煲汤紫砂锅官方陶瓷燕窝_苏泊尔4L电饭煲煮饭锅球釜家用官方智能6旗舰店5正品小1-2-3-4人_苏泊尔养生煎药壶家用电砂锅熬药锅中药锅煎药全自动煮茶中医陶瓷_苏泊尔电炖锅小熬煮粥锅陶瓷紫砂锅煲汤神器家用1人2全自动电炖盅_苏泊尔电蒸锅多功能家用304不锈钢大容量自动断电蒸笼蒸菜蒸汽锅_苏泊尔多功能养生壶电全自动加厚玻璃小迷你家用保温煮茶壶办公室_苏泊尔电饭煲智能5L大容量家用1煮饭锅2官方旗舰店3正品4-5-6-8人_苏泊尔烧水壶自动玻璃电热水壶茶304不锈钢家用大容量透明开水器_苏泊尔养生壶全自动加厚玻璃多功能煮茶官方旗舰店家用电热烧水壶_",
  "老板电器": "Robam/老板电器26A7+58B1侧吸式欧式抽油烟机燃气灶套餐烟灶套装_Robam/老板电器67A7+58B1/58G6欧式抽油烟机燃气灶具套餐烟灶套装_Robam/老板60X3+30B3顶吸抽油烟机燃气灶套装免拆洗电器套餐包邮_Robam/老板67X6H+58B1 抽油烟机大吸力套餐顶吸欧式电器烟灶套装_Robam/老板CXW-200-65X6抽油烟机顶吸式大吸力品牌电器8325升级_Robam/老板26A7电器品牌全黑触屏控智能抽油烟机侧吸式大吸力烟机_Robam/老板CXW-200-21X3老板油烟机侧吸式吸抽油烟机电器正品_Robam/老板R073+S273新品烤箱蒸箱嵌入式家用套装蒸烤箱套餐电器_电器城Robam/老板30B3 新聚中劲火嵌入式燃气灶 高效节能_Robam/老板ZTD100B-727T 消毒柜家用嵌入式旗舰店电器紫外线杀菌_",
  "花花公子": "花花公子男士长袖t恤圆领加绒卫衣秋季纯棉男装潮流打底衫上衣服_花花公子男士牛仔裤男宽松直筒弹力中年加绒加厚休闲长裤子秋冬款_花花公子2018青年男士针织衫毛衣春秋装开衫外套长袖T恤薄款线衫_花花公子冬季加绒加厚青年圆领新款保暖针织衫时尚潮T恤打底毛衣_花花公子长袖T恤男秋装潮流加绒打底衫外穿秋衣卫衣男装秋季上衣_花花公子长袖T恤男 中年纯棉男装保罗衫春秋装翻领休闲男士polo衫_花花公子衬衫男长袖2018秋季新款潮流印花上衣男装长袖花衬衣男款_花花公子长袖t恤男士秋季男装卫衣保暖打底衫体恤印花潮流上衣服_花花公子羊毛衫男冬季款厚款高领毛衣男士修身韩版纯色套头针织衫_花花公子长袖t恤男秋装新款圆领印花卫衣 中青年时尚男装休闲卫衣_花花公子卫衣男韩版修身青年加厚加绒开衫男士毛衣秋冬连帽外套男_花花公子针织衫男秋季加绒男士修身毛衣圆领青年学生长袖T恤男装_花花公子冬季毛衣男加绒加厚圆领套头男士纯色保暖针织衫毛线衣潮_花花公子羽绒裤中老年人加厚防风保暖棉裤男女士冬季内外穿爸爸装_花花公子正品牛仔裤男秋季新款修身青年商务男士宽松直筒长裤子潮_花花公子男士长袖t恤圆领加绒卫衣秋季纯棉男装潮流打底衫上衣服_花花公子男士牛仔裤男宽松直筒弹力中年加绒加厚休闲长裤子秋冬款_花花公子2018青年男士针织衫毛衣春秋装开衫外套长袖T恤薄款线衫_花花公子冬季加绒加厚青年圆领新款保暖针织衫时尚潮T恤打底毛衣_花花公子长袖T恤男秋装潮流加绒打底衫外穿秋衣卫衣男装秋季上衣_花花公子长袖T恤男 中年纯棉男装保罗衫春秋装翻领休闲男士polo衫_花花公子衬衫男长袖2018秋季新款潮流印花上衣男装长袖花衬衣男款_花花公子长袖t恤男士秋季男装卫衣保暖打底衫体恤印花潮流上衣服_花花公子羊毛衫男冬季款厚款高领毛衣男士修身韩版纯色套头针织衫_花花公子长袖t恤男秋装新款圆领印花卫衣 中青年时尚男装休闲卫衣_花花公子卫衣男韩版修身青年加厚加绒开衫男士毛衣秋冬连帽外套男_花花公子针织衫男秋季加绒男士修身毛衣圆领青年学生长袖T恤男装_花花公子冬季毛衣男加绒加厚圆领套头男士纯色保暖针织衫毛线衣潮_花花公子羽绒裤中老年人加厚防风保暖棉裤男女士冬季内外穿爸爸装_花花公子正品牛仔裤男秋季新款修身青年商务男士宽松直筒长裤子潮_花花公子冬季加绒加厚男裤中年直筒修身裤子高弹力商务免烫休闲裤_花花公子长袖t恤男秋冬款韩版上衣男士纯色体恤POLO衫青年男装T恤_花花公子长袖t恤男士修身翻领体恤衫青年纯棉打底衫潮流男装秋季_花花公子秋冬款卫衣男加绒外套韩版休闲青年加厚毛衣拉链开衫男装_花花公子加绒加厚牛仔裤男士秋冬款直筒弹力大码休闲宽松长裤子男_",
  "海信": "Hisense/海信HZ32E30D 32英寸蓝光高清平板液晶电视机彩电_Hisense/海信HZ43E35A 43寸AI 智能高清 WiFi智能网络平板电视机_Hisense/海信HZ43E35A 43英寸高清智能WIFI网络平板液晶电视_Hisense/海信HZ32E35A 32英寸高清智能WIFI网络卧室液晶电视机_Hisense/海信HZ39E35A 39英寸高清智能WIFI网络平板液晶电视40_Hisense/海信HZ32E30D 32英寸液晶电视机家用高清平板特价小彩电_Hisense/海信HZ32E35A 高清32英寸家用WIFI网络平板液晶电视机_Hisense/海信HZ32E35A 32吋液晶电视机网络智能wifi特价家用平板_Hisense/海信LED75E7U 75吋4K高清智能网络平板液晶电视机_Hisense/海信HZ32E35A 32英寸高清WIFI智能网络平板液晶电视机_Hisense/海信HZ32E30D 32英寸蓝光高清平板液晶电视机彩电_电视机32吋 LED高清智能WIFI网络平板液晶Hisense/海信HZ32E35A_Hisense/海信HZ39E35A 39英寸高清网络智能wifi平板液晶电视机40_Hisense/海信LED55E7CY 55吋4K曲面智能高清网络平板液晶 电视机_Hisense/海信LED75E7U 75吋4K高清智能网络平板液晶电视机_Hisense/海信HZ32E35A 32英寸新品智能高清网络平板液晶电视机_Hisense/海信HZ32E30D 32英寸蓝光高清平板液晶电视机老人彩电_Hisense/海信LED75E7U 75英寸4K高清智能网络平板液晶电视机_Hisense/海信HZ39E30D 39英寸蓝光高清平板液晶电视机家用彩电40_Hisense/海信LED60EC500U 60吋4K高清智能网络平板液晶电视机_Hisense/海信HZ43E35A 43英寸高清智能WIFI网络平板液晶电视_Hisense/海信LED49EC500U 49英寸4K高清智能网络平板液晶电视机_Hisense/海信HZ55E52A 55英寸4K高清智能平板液晶AI全面屏电视机_",
  "美特斯邦威": "美特斯邦威男装长裤休闲经典官方旗舰店跑裤春秋季新款男裤748017_美特斯邦威牛仔裤男装春秋季新款官方旗舰店休闲舒适牛仔裤756224_美特斯邦威男装旗舰店棒球服外套韩版短款显瘦茄克青少年官方正品_美特斯邦威官方旗艦店开衫卫衣男装2018秋季新款加绒潮流连帽外套_美特斯邦威官方旗艦店牛仔裤男装2018秋季新款小脚潮流修身长裤子_美特斯邦威男装旗舰店梭织长裤男裤春秋装新款休闲裤子官方正品_美特斯邦威衬衫男潮流韩版秋装纯棉印花上衣男士休闲商务长袖衬衣_美特斯邦威男装旗舰店牛仔裤男士冬装新款干净棉弹长裤官方正品_美特斯邦威男牛仔长裤2017秋季新款男五袋常年洗水官方旗舰店男装_美特斯邦威休闲长裤官方旗舰店男装秋季新款商务裤子韩版直筒_美特斯邦威男装旗舰店休闲裤春秋装新款裤子青年小脚长裤官方正品_美特斯邦威官方旗艦店休闲裤男装春秋季新款迷彩裤子男宽松工装裤_美特斯邦威休闲裤秋季新款官方旗舰店男装潮流直筒长裤子青年_美特斯邦威官方旗艦店卫衣男装2018秋季新款休闲学生套头运动外套_美特斯邦威男装旗舰店束脚长裤男秋新款潮流男裤子官方正品_美特斯邦威男装牛仔裤男秋季韩版潮流裤子修身长裤学生休闲小脚裤_美特斯邦威男裤子 春秋款 百搭男士中腰纯棉修身小脚黑色休闲长裤_美特斯邦威男裤子 春秋季 男士中腰全棉质修身直筒黑色休闲裤长裤_美特斯邦威男装旗舰店休闲裤春秋装新款纯棉潮流直筒长裤官方正品_美特斯邦威官方旗艦店卫衣男装长袖2018秋季新款潮流休闲套头外套_美特斯邦威官方旗艦店短袖T恤男装夏季打底衫棉纯色圆领美邦体恤_美特斯邦威官方旗艦店格子衬衫男长袖韩版潮2018春秋棉麻衬衣男装_美特斯邦威牛仔裤男秋季官方旗艦店男装潮流裤子男韩版修身小脚裤_美特斯邦威男装旗舰店开衫卫衣男春装新款外套男学生韩版官方正品_美特斯邦威男装旗舰店冬装新款休闲裤子男运动韩版小脚裤官方正品_美特斯邦威毛衣男装2018秋季新款撞色圆领毛线衣潮流青少年针织衫_美特斯邦威官方旗艦店休闲裤男装2018秋装新款宽松多袋工装裤子男_美特斯邦威卫衣男装开衫连帽纯色2018秋季新款韩版潮流青少年外套_美特斯邦威黑色牛仔裤男士中腰标准直筒裤子男裤休闲宽松长裤秋季_",
  "思莱德": "思莱德男款冬季四双装中筒袜 棉质袜秋季运动简约商务百搭长袜子_思莱德秋冬季男士保暖四双装中筒袜 运动简约商务百搭棉质长袜子_Siti Selected欧美大气无袖毛呢短外套女纯色不规则显瘦背心女潮_Siti Selected黑色圆领毛边蕾丝衬衫长袖欧美风直筒气质上衣秋女_Siti Selected灰色格子仿羊羔毛毛呢外套连帽直筒英伦风上衣秋女_Siti Selected新款红色宽松高领毛衣套头百搭通勤毛线上衣秋季女_Siti Selected咖啡色圆领泡泡袖连衣裙通勤收腰大摆褶皱中长裙女_Siti Selected新款白色圆领刺绣长袖卫衣灯笼袖百搭清新上衣秋女_Siti Selected蓝色做旧天丝牛仔阔腿裤简约宽松裙裤毛边长裤夏女_Siti Selected小香风格子毛边毛呢外套西装领直筒长款上衣秋冬女_Siti Selected新款白色长袖圆领衬衫棉蕾丝拼接宽松打底衫中长款_Siti Selected红色高领镂空套头毛衣原创下摆设计复古秋冬上衣女_Siti Selected驼色仿羊羔毛拼接袖复合麂皮绒外套连帽撞色上衣女_Siti Selected深蓝色喇叭高腰牛仔裤复古欧美提臀百搭长裤秋冬女_Siti Selected红白条纹撞色长袖衬衫裙通勤中长连衣裙_Siti Selected咖色复古格子粗花呢背心连衣裙无袖方领一步裙秋女_Siti Selected白色水溶蕾丝七分裤高腰显瘦气质阔腿裤夏季裙裤女_Siti Selected粉色绣花复合麂皮绒圆领卫衣宽松欧美风上衣秋季女_Siti Selected黑色格子拼接卫衣半高领宽松时尚假两件连衣裙秋女_Siti Selected新款白色高领短款卫衣收腰撞色百搭磨毛秋季上衣女_Siti Selected深灰色字母印花连帽套头卫衣青春百搭通勤秋上衣女_Siti Selected白色长袖蝴蝶结衬衫黑色包臀不规则鱼尾半身裙套装_Siti Selected新款大毛领迷彩羽绒服女中长款加厚欧美冬装外套_Siti Selected新款黑色波点透视雪纺衬衣长袖木耳边性感上衣秋女_Siti Selected红色工装大毛领羽绒服女中长款收腰冬2018新款派克_Siti Selected白色波点印花长袖衬衫方领宽松通勤百搭上衣秋季女_Siti Selected新款灰色字母刺绣套头卫衣长袖百搭潮流宽松上衣女_Siti Selected新款黑白条纹圆领长袖针织衫套头时尚内搭毛衣女_Siti Selected新款灰蓝色刺绣牛仔裤高腰做旧百搭直筒小脚裤秋女_",
  "格兰仕": "Galanz/格兰仕G70D20CN1P-D2(SO)微波炉烤箱一体家用小型光波炉_Galanz/格兰仕P70F20CN3P-SR(W0) 家用微波炉 智能真平板 正品_Galanz/格兰仕G70D20CN1P-D2(SO) 电脑版转盘式家用微波炉光波炉_Galanz/格兰仕G70D20CN1P-D2(SO)家用微波炉转盘式 智能光波炉_Galanz/格兰仕P70F23P-G5(SO)机械式家用微波炉23升平板式特价_Galanz/格兰仕P70F20CN3P-Q1(W0)家用微波炉智能平板微波炉正品_Galanz/格兰仕P70F23P-G5(SO)家用旋钮机械式23升平板式微波炉_Galanz/格兰仕P70F23P-G5(SO) 微波炉机械式家用平板光波炉23升_Galanz/格兰仕G70D20CN1P-D2(SO)家用微波炉智能光波炉烧烤一体_Galanz/格兰仕G70D20CN1P-D2(SO)转盘微波炉烤箱一体家用光波炉_【抢】格兰仕电烤箱家用烘焙多功能全自动小蛋糕电烤箱30升大容量_Galanz/格兰仕G80F23CN3L-Q6(W0) 23L微波炉 光波炉蒸汽烧烤智能_Galanz/格兰仕G70F20CN3L-C2(S2)光波炉家用微波炉智能平板_Galanz/格兰仕P70D20TL-D4 20L转盘机械式家用微波炉全国联保_Galanz/格兰仕P70F20CN3P-N9(WO) -DG(SO)机械光波炉微波炉烤箱_Galanz/格兰仕SD-G238W(S0D)智能平板微波炉 家用光波炉烤箱一体_✅Galanz/格兰仕G90F25CN3L-C2(G2)家用智能光波微波炉 烤箱一体_Galanz/格兰仕G90F25CN3L-C2(G2)家用智能微波炉光波炉包邮_Galanz/格兰仕P70F20CL-DG(B0) 微波炉20L家用平板式手拉速热_Galanz/格兰仕G70F20N2L-DG(SO)家用机械式光波炉微波炉烤箱一体_Galanz/格兰仕G70F20N2L-DG(SO)-ZS(W0))机械式微波炉烤箱一体_Galanz/格兰仕SD-G238W(S0D)微波炉烤箱一体家用 蒸汽光波炉正品_Galanz/格兰仕G80F23CN3LN-C2(C0) 微波炉家用智能光波炉平板式_Galanz/格兰仕G70D20CN1P-D2(SO)家用微波炉智能光波炉特价_Galanz/格兰仕G70F20CN1L-DG(B0)家用平板微波炉光波炉 烤箱一体_Galanz/格兰仕G70D20CN1P-D2(SO)微波炉烤箱一体家用小型光波炉_格兰仕G70F20CP-D2(S0) 平板微波炉 家用小型光波炉烤箱一体新款_Galanz/格兰仕P70F20CL-DG(B0) 微波炉20L家用平板手拉速热_Galanz/格兰仕G70F20CN1L-DG(B1)家用微波炉光波炉烤箱一体平板_",
  "森马": "森马衬衫男长袖2018春秋装新款男士衬衣纯棉韩版潮流青少年寸衫_森马ulzzang衬衫男长袖春秋装男士纯棉寸衫个性印花韩版休闲寸衣_森马官方店牛仔裤男春秋款男士精神小伙小脚裤韩版弹力束脚潮运动_森马衬衫男长袖春秋装新款男装个性韩版潮帽衫纯棉印花连帽寸衣_森马毛衣男潮2018春秋装新款男士圆领针织衫毛衫韩版毛线衣青年_森马棉服马甲男2018春秋装新款男士韩版潮流外套青少年衣服外衣潮_森马官方店衬衫男长袖2018春秋装新款男生白色衬衣纯棉韩版帅气_森马官方店毛衣男潮春秋装男装潮流线衫针织衫青少年_森马官方店男士风衣2018新款中长款薄外套韩版潮流休闲_森马官方店毛衣男韩版春秋季纯棉男装针织衫学生线衫青少年_森马夹克男2018春秋装新款男士休闲外套薄韩版潮流hiphop外套青年_森马官方店休闲裤男春秋款男装黑色长裤运动裤工装裤子潮_森马官方店毛衣男韩版潮2018春秋装新款男士V领针织衫开衫外套_森马官方店衬衫男长袖2018春秋装新款男士夹克韩版潮流学生boy_森马套装男2018秋季新款男装黑色长袖卫衣休闲裤针织运动服两件套_森马棉服男2018冬季新款加绒保暖棉夹克男士时尚立领青少年外套_森马官方店牛仔裤男直筒2018夏季新款裤子男韩版潮破洞长裤_森马针织衫 冬装新款 男士长袖印花毛衫套头毛衫毛衣韩版潮流_森马官方店夹克男2018春秋款薄款连帽运动外套男韩版潮流修身帅气_森马衬衫男长袖2018春秋款新款男士白衬衣潮牌帅气青少年打底寸衫_森马羽绒马甲男2018冬季新款男士立领保暖坎肩韩版休闲轻薄背心潮_森马官方店九分休闲裤2018春秋款男士抽绳束脚户外运动裤韩版潮_森马官方店卫衣男连帽 春秋装男士韩版潮流衫帽衫学生杨洋上衣_森马官方店毛衣男潮2018春秋装新款男士圆领毛线衣韩版长袖针织衫_森马官方店衬衫男长袖2018春秋装新款男士衬衣青少年纯棉寸衫_森马官方店衬衫男长袖2018春秋装新款男士纯棉衬衣条纹寸衫青年_森马棉服男2018冬季新款短款仿羊羔绒外套男士毛领灯芯绒加绒棉袄_森马毛衣男2018春秋款新款男士韩版假两件针织衫潮流条纹线衣线衫_森马牛仔裤男2018秋款合体小直筒长裤11058241019 11-058241019_",
  "巴拉巴拉": "巴拉巴拉儿童套装男童宝宝秋装2018新款运动两件套小童男休闲连帽_巴拉巴拉童装儿童套装男童秋装2018新款中大童衣服男两件套卫衣薄_巴拉巴拉童装儿童羽绒马甲小童宝宝秋冬2018新款男童轻薄保暖背心_巴拉巴拉儿童羽绒马甲男童轻薄连帽背心2018秋冬新款中大童坎肩潮_巴拉巴拉儿童裤子男长裤2018新款秋冬中大童男童加绒印花休闲裤潮_巴拉巴拉童装男童套装中大童儿童两件套春秋装2018新款圆领卫衣潮_巴拉巴拉男童套装运动秋装018新款童装中大童卫衣裤子儿童两件套_巴拉巴拉童装儿童套装男童秋装2018新款中大童男两件套卫衣裤子潮_巴拉巴拉童装婴幼儿宝宝羽绒服哈衣男女童加厚连体爬服外出抱衣_巴拉巴拉童装儿童套装男童秋装2018新款中大童两件套28043181101_巴拉巴拉童装男童外套秋装2018新款儿童防风衣男中大童户外冲锋衣_巴拉巴拉男童外套儿童冲锋衣秋装2018新款防风外衣潮21053171208_巴拉巴拉男幼童儿童厚背带裤羽绒裤2018冬装新款包邮21084171211_巴拉巴拉童装男童冲锋衣防风秋冬2018新款中大童棉服儿童保暖外套_巴拉巴拉男童外套春秋装2018新款两面中大童22051181607_巴拉巴拉男幼童羽绒裤2018冬装新款童装男童宝宝帅气长裤加厚裤子_巴拉巴拉官方旗舰男童外套2018秋装新款中大童儿童户外冲锋衣潮_巴拉巴拉男童棉衣2018新款韩版棉服小童儿童加厚棉袄外套冲锋衣潮_巴拉巴拉婴儿爬爬服轻薄羽绒服连体衣冬季新生儿男女宝宝_巴拉巴拉儿童套装男童两件套秋装2018新款中大童长袖运动套装卫衣_巴拉巴拉童装男童套装中大童外套儿童两件套春装2018新款运动卫衣_巴拉巴拉儿童羽绒服马甲男童羽绒背心中大童坎肩秋冬新款反季短款_巴拉巴拉官方旗舰女童羽绒马甲2018冬装新款儿童中大童加厚外套潮_",
  "夏普": "Sharp/夏普2T-C32ACSA/ZA 32英寸 高清安卓智能网络液晶平板电视_Sharp/夏普LCD-32DS16A 32英寸 高清安卓智能网络液晶平板电视机_Sharp/夏普32B4HA 32英寸家用高清液晶平板网络电视机40 42_Sharp/夏普2T-C32ACSA/ZA 32英寸 高清安卓智能网络液晶平板电视_Sharp/夏普电视32寸2T-C32ACSA高清安卓网络智能Wifi液晶电视特价_Sharp/夏普LCD-70SU678A 70英寸4K超高清智能液晶平板电视机60_夏普/Sharp LCD-45TX4100A 电视机45寸网络智能高清wif i电视55寸_Sharp/夏普LCD-70MY5100A  70英寸4K网络智能平板液晶电视机_PANDA/熊猫 39F4S 39英寸夏普技术蓝光高清液晶平板电视机特价40_Sharp/夏普60M4AA 60英寸4K超高清智能网络液晶电视官方旗舰店55_原装夏普MX-237CT墨粉MX-238CT粉盒 2048s/2048D/2048N/2348s/2348D/2348N/2648N/3148N碳粉_原装夏普MX-235/MX-236粉盒ar1808s/2008D/2308N/2008L/2308D/2328/2035/碳粉MX-236粉盒M2308D/MX-M2028D_夏普车载空气净化器 IG-HC15 JC15汽车氧吧负离子除异味甲醛PM2.5_夏普CS-2122H插电源LED荧光屏电脑按键计算器银行财务用计算机_原装夏普AL-103T粉盒夏普复印机AL-1035-WH AL-1031-WH墨粉 碳粉_原装正品夏普MX-B20CT1 粉盒 AR- 2038 2038D 2038F 墨粉 碳粉_",
  "马克华菲": "马克华菲秋冬新款长袖衬衫方领印花上衣_马克华菲长袖T恤男韩版纯棉2018秋季新款春秋装衣服打底衫上衣_马克华菲长袖T恤男装2018秋季韩版新款衣服男打底衫薄款上衣圆领_马克华菲长袖t恤男2018秋季新款高领修身韩版打底衫男装上衣春秋_马克华菲针织衫男装毛衣2018秋季新款纯棉圆领纯色简约秋冬打底衫_商场同款马克华菲毛呢大衣男冬新品植绒印花外套716416022054_马克华菲外套男连帽2018秋季新款韩版春秋运动男士抓绒外衣夹克_马克华菲卫衣男连帽2018秋季新款刺绣韩版休闲装秋装帽衫春秋外套_马克华菲高领毛衣男士针织衫2018秋季新款纯色秋冬纯棉打底衫线衫_马克华菲牛仔裤男2018秋季男裤直筒修身小脚裤男装新款裤子休闲裤_马克华菲长袖t恤男2018秋季新款韩版春秋男士圆领春秋印花打底衫_商场同款马克华菲中袖衬衫男新品印花上衣白衬衣717103031002_马克华菲休闲裤男2018秋季男裤男士加绒加厚保暖运动裤冬束脚裤子_马克华菲长袖t恤男2018秋季新款韩版春秋黑色印花套头休闲上衣_马克华菲夹克男士外套2018秋季修身新款飞行员休闲棒球服春秋男_马克华菲中长款风衣男2018秋季新款红色连帽外套休闲韩版上衣男装_马克华菲长袖衬衫男休闲韩版潮流帅气格子字母印花上衣衬衫_马克华菲t恤男长袖2018秋季新款打底衫韩版修身纯棉秋衣潮流刺绣_马克华菲休闲裤男运动裤2018秋季束脚小脚长裤新款裤子男装卫裤_马克华菲长袖T恤男白色2018秋季新款印花打底衫春秋纯棉体恤上衣_马克华菲夹克男士外套2018秋季新款韩版春秋白色棒球服休闲男装_马克华菲长袖t恤男2018秋季新款韩版春秋黑色圆领套头印花上衣_马克华菲长袖t恤男2018秋季新款韩版春秋男士圆领修身上衣打底衫_马克华菲长袖T恤男士2018秋季新款纯棉圆领修身秋衣男打底衫小衫_马克华菲长袖衬衫男2018秋季新款韩版秋装修身衬衣内搭男装上衣_马克华菲牛仔裤男秋季2018新款韩版男裤男士修身直筒小脚裤长裤_马克华菲牛仔裤男2018秋季新款韩版裤子男士直筒修身休闲男裤长裤_马克华菲牛仔裤男秋季新款裤子束脚裤哈伦裤男裤韩版修身休闲长裤_马克华菲黑色外套男连帽2018新款秋季春秋男士宽松外衣夹克秋装_",
  "杰克琼斯": "杰克琼斯韩版秋加绒内里水洗加厚保暖个性男长牛仔裤子217132520_杰克琼斯韩版秋青年纯棉休闲长裤小脚水洗男牛仔裤子217132552_杰克琼斯弹力专柜正品春秋方领修身纯棉长袖牛仔上衣男士牛仔衬衫_杰克琼斯韩版秋厚含莱卡棉印花内里修身男长牛仔裤子217132534_杰克琼斯新款高弹力修身男装秋季休闲时尚水洗牛仔长裤217232502_杰克琼斯新款韩版浅色弹力舒适秋季低裆修身男士牛仔裤长裤子_杰克琼斯含莱卡棉新款韩版修身男装秋季水洗长牛仔裤217232506_杰克琼斯新款韩版秋季商务潮男休闲百搭男纯棉翻领长袖衬衫男衬衣_杰克琼斯春秋新款男装进口棉弹力做旧破洞磨白牛仔长裤217332528_杰克琼斯韩版秋修身小脚青年潮天丝磨破男牛仔长裤子217132565_杰克琼斯新款时尚泼墨印花直筒秋冬男装圆领套头卫衣E|218133533_杰克琼斯男士新款夏季时尚修身黑色纯棉印花圆领针织休闲短袖T恤_杰克琼斯正品潮字母新款韩版休闲棉宽松圆领男士秋冬运动套头卫衣_杰克琼斯国内专柜纯棉休闲撞色条纹男士夏长袖衬衫衣218105514_专柜正品杰克琼斯夏季修身方领纯色韩版白色纯棉休闲男士衬衣衬衫_杰克琼斯国内专柜夏季纯棉修身薄男装羊毛中低腰男士长裤休闲裤子_杰克琼斯韩版秋青年深色弹力纯棉修身小脚男长牛仔裤子217132512_国内专柜杰克琼斯秋季罗文修身长袖男士外套男装夹克防晒衣上衣_杰克琼斯韩版泼墨补丁破洞秋青年纯棉无弹男休闲长乞丐裤男牛仔裤_杰克琼斯国内专柜专柜新款夏季纯棉长袖薄款翻领青年男士衬衫衬衣_杰克琼斯国内专柜MLMR士秋冬磨毛纯棉宽松格纹长袖衬衫218105506_杰克琼斯国内专柜代购夏季纯棉长袖薄款翻领水洗青年男士衬衫衬衣_杰克琼斯国内专柜夏季韩版休闲男士尖领纯棉网眼拼接长袖衬衣衬衫_杰克琼斯新款小束脚男士秋装运动时尚舒适休闲长卫裤子217314507_杰克琼斯新款夏季纯棉时尚短袖T恤男 包邮百搭个性商务休闲POLO衫_杰克琼斯国内专柜专柜新款夏季亚麻长袖薄款翻领品牌男士衬衫衬衣_专柜正品杰克琼斯男秋冬羊毛英伦格纹修身单西装外套el217308510_杰克琼斯新款男莱卡棉抽绳腰头松紧裤脚锥形弹力收口运动牛仔长裤_",
  "松下": "松下吹风机家用女负离子理发店冷热风不伤发折叠便携大功率电吹风_松下吹风机女家用大功率负离子理发店不伤发宿舍静音冷热电吹风筒_松下电动剃须刀充电式往复式全身水洗刮胡刀子男士电动胡须刀正品_日本制造松下ES-RS10电动剃须刀男士干电池式刮胡刀迷你便携出差_松下吹风机家用学生大功率不伤发吹风筒宿舍网红款电吹风理发店女_松下负离子发梳EH-HE10VP 负离子造型梳直发便携美发器_松下电动剃须刀往复充电式男士胡须刀刮胡刀子全身水洗刮胡刀正品_松下电动剃须刀全身水洗充电式男士剔胡须刀递须刨刮胡刀原装正品_松下电吹风机家用理发店不伤发静音负离子网红款冷热风筒大功率女_松下电吹风机女家用负离子大功率理发店不伤发折叠式冷热吹风筒男_✅松下电器官方旗舰店官网大功率负离子吹风机家用 理发店 不伤发_松下电动剃须刀es518便携式小巧男士剃须刀干电池卡片式超薄正品_松下吹风机女家用新款理发店便携式不伤发静音冷热风负离子电吹风_松下电动往复式充电式剃须刀ES-WSL7D 男刮胡刀胡须刀全身水洗_松下负离子电吹风机网红款家用大功率理发店不伤发吹风筒冷热女6B_松下男士剃须刀电动往复式剃胡刀刮胡子刀电动充电式3刀头胡须刀_松下剃须刀电动充电式胡须刀往复式全身水洗男士智能刮胡刀正品_Panasonic/松下电动理发器ER-GC51家庭成人儿童电推剪 充电式防水_松下吹风机家用理发店不伤发负离子静音恒温日本大功率冷热风筒_松下电动剃须刀刮胡刀充电往复式男士刮胡刀电动胡须刀子全身水洗_松下吹风机家用理发店不伤发负离子大功率吹风筒宿舍用电吹风女2H_松下吹风机家用理发店不伤发负离子电吹风大功率冷热风筒女风大_松下剃须刀ES5821卡式刮胡刀充电电须刀轻薄机身携带方便出差旅行_松下吹风机家用大功率负离子不伤发学生迷你静音冷热电吹风WNE5D_松下负离子电吹风机家用不伤发学生小功率宿舍用风筒理发店女NE11_松下电吹风机女家用理发店不伤发小大功率负离子吹风筒静音冷热风_松下电吹风机EH-WNE5C家用冷热风负离子电吹风 大功率护发吹风筒_松下剃须刀往复式电动充电式男士胡须刀干湿双剃刮胡刀全身水洗_日本松下剃须刀男士电动充电式刮胡刀往复原装进口胡须刀 ES-ST29_",
  "好奇": "好奇铂金装纸尿裤S96*2 超薄透气婴儿尿不湿男女宝宝官方旗舰店_好奇金装纸尿裤L129 倍柔贴身婴儿尿不湿男女宝宝通用 官方旗舰店_好奇铂金装纸尿裤婴儿尿不湿倍柔亲肤L76*2箱男女宝宝官方旗舰店_好奇铂金装婴儿新生儿0-3个月宝宝s码尿不湿小号纸尿裤S初生96片_好奇金装纸尿裤M162 倍柔贴身婴儿尿不湿男女宝宝通用 官方旗舰店_好奇银装纸尿裤XL104干爽舒适婴儿尿不湿男女宝宝通用官方旗舰店_好奇铂金装纸尿裤M92*2超薄透气婴儿尿不湿男女通用 官方旗舰店_好奇铂金装纸尿裤XL64 超薄透气新生儿尿不湿男女通用 官方旗舰店_好奇铂金装纸尿裤L76*2 超薄透气婴儿尿不湿男女宝宝官方旗舰店_好奇铂金装纸尿裤XL64*2婴儿超薄透气男女宝宝尿不湿 官方旗舰店_好奇铂金装纸尿裤NB84+S76＋棉柔巾80抽 超薄透气尿不湿 男女宝宝_好奇心钻装纸尿裤新生儿尿不湿男女宝宝通用NB66 官方旗舰店_好奇心钻装纸尿裤新生儿尿不湿男女宝宝通用NB66 官方旗舰店_好奇银装纸尿裤L128 干爽舒适婴儿尿不湿男女宝宝通用 官方旗舰店_好奇小猪佩奇铂金拉拉裤XL136婴儿超薄透气加大号成长裤男女宝宝_好奇金装倍柔贴身纸尿裤婴儿尿不湿M162片男女宝宝 官方旗舰店_好奇金装成长裤XL72 超薄透气拉拉裤学步裤男女通用   官方旗舰店_好奇银装成长裤L100 干爽舒适拉拉裤学步裤男女通用 官方旗舰店_好奇铂金装倍柔亲肤纸尿裤箱装S96片*2婴儿尿不湿 官方旗舰店_好奇银装纸尿裤M160 干爽舒适婴儿尿不湿男女宝宝通用 官方旗舰店_好奇铂金装纸尿裤M92*2超薄透气婴儿尿不湿男女通用  官方旗舰店_好奇心钻装纸尿裤新生儿尿不湿男女宝宝通用S62 官方旗舰店_【韩版上市】好奇铂金装新版婴儿纸尿裤NB66+14片 透气正品尿不湿_好奇铂金装成长裤XL64 超薄透气拉拉裤男女通用学步裤 官方旗舰店_好奇铂金装成长裤L76超薄透气拉拉裤男女通用学步裤   官方旗舰店_好奇心钻装纸尿裤新生儿尿不湿男女宝宝通用S62 官方旗舰店_好奇铂金装纸尿裤NB84*2超薄透气新生儿尿不湿男女通用官方旗舰店_好奇小猪佩奇铂金成长裤XL136婴儿超薄透气加大号拉拉裤男女宝宝_【官方正品】进口好奇铂金装婴儿纸尿裤s宝宝透气尿不湿S76片*3包_",
  "安奈儿": "安奈儿童装男童保暖外套冬季中大童加厚夹棉格子棉衣EB645403_安奈儿童装男童冬装加厚双层夹棉全腰针织牛仔棉裤长裤AB746783_安奈儿童装女童轻薄羽绒服秋冬2018新款洋气男孩亲子装外套短款潮_安奈儿童装男童保暖外套冬季中大童加厚夹棉格子棉衣EB645403_安奈儿童装男童冬装加厚双层夹棉全腰针织牛仔棉裤长裤AB746783_安奈儿童装女童轻薄羽绒服秋冬2018新款洋气男孩亲子装外套短款潮_安奈儿童装男童春秋装纯棉运动套装T恤长裤两件套AB711504特价_安奈儿童装男童冬装加厚双层夹棉全腰针织棉裤长裤AB746792正品_安奈儿童装男童春秋装短款梭织夹克外套上衣棒球服AB715601正品_安奈儿童装男童梭织风衣外套2018春装新款中大童连帽外套EB715101_安奈儿童装男童春秋装纯棉翻领长袖针织衫T恤打底衫AB731504正品_安奈儿童装女童家居服 2016秋冬装中大儿童加厚睡衣套装JG635938_安奈儿童装男童秋冬装运动休闲加厚加绒全腰针织长裤AB746773正品_安奈儿童装女童秋冬装纯棉长袖高翻领棉线衫毛衣线衣AG734737正品_安奈儿童装男童长袖T恤针织衫2018秋新款字母棉弹打底衫AB831515_安奈儿童装女童保暖加厚夹棉家居服中大儿童睡衣套装JG635938_安奈儿童装2018秋新款中大女童修身亲子装牛仔裙连衣裙子AG533508_安奈儿男童马甲2018秋装新款正品中大童针织外套背心马夹EB732302_安奈儿童装男童秋冬装加厚加绒全腰针织牛仔长裤AB746722正品特价_安奈儿童装男童运动外套新款秋冬装中大童加厚薄棉衣_安奈儿童装男童保暖外套冬季中大童加厚夹棉格子棉衣EB645403_安奈儿童装男童冬装加厚双层夹棉全腰针织牛仔棉裤长裤AB746783_安奈儿童装女童轻薄羽绒服秋冬2018新款洋气男孩亲子装外套短款潮_安奈儿童装男童春秋装纯棉运动套装T恤长裤两件套AB711504特价_安奈儿童装男童冬装加厚双层夹棉全腰针织棉裤长裤AB746792正品_安奈儿童装男童春秋装短款梭织夹克外套上衣棒球服AB715601正品_安奈儿童装男童梭织风衣外套2018春装新款中大童连帽外套EB715101_安奈儿童装男童春秋装纯棉翻领长袖针织衫T恤打底衫AB731504正品_安奈儿童装女童家居服 2016秋冬装中大儿童加厚睡衣套装JG635938_安奈儿童装男童秋冬装运动休闲加厚加绒全腰针织长裤AB746773正品_安奈儿童装女童秋冬装纯棉长袖高翻领棉线衫毛衣线衣AG734737正品_安奈儿童装男童长袖T恤针织衫2018秋新款字母棉弹打底衫AB831515_安奈儿童装女童保暖加厚夹棉家居服中大儿童睡衣套装JG635938_安奈儿童装2018秋新款中大女童修身亲子装牛仔裙连衣裙子AG533508_安奈儿男童马甲2018秋装新款正品中大童针织外套背心马夹EB732302_安奈儿童装男童秋冬装加厚加绒全腰针织牛仔长裤AB746722正品特价_安奈儿童装男童运动外套新款秋冬装中大童加厚薄棉衣_安奈儿童装男童秋冬装运动休闲加厚加绒全腰针织长裤AB746772正品_安奈儿童装女童家居服 2016秋冬装中大儿童加厚睡衣套装JG635938_安奈儿童装男童秋冬装双层加厚加绒全腰针织夹裤长裤AB746777正品_安奈儿童装女大童秋冬款女童礼服_安奈儿童装女童秋冬装加厚加绒全腰针织牛仔裤长裤AG746735正品特_安奈儿童装男童外套2018秋冬装新款中长款两件套棉衣棉服EB645401_安奈儿童装女童秋冬新款女童带帽长袖礼服_安奈儿男童装秋冬装加厚加绒牛仔外套棉衣AB545506特价专柜正品_安奈儿童装正品2018秋装新款女小童圆领长袖裙衣 连衣裙XG831583_安奈儿童装女小童棉线毛衣长袖连衣裙2018秋冬装新款裙衣XG734783_安奈儿童装男童风衣连帽秋冬装2018新款洋气加绒加厚男孩保暖外套_安奈儿童装2018冬季新款女童连帽羽绒马甲中大童时尚卡通背心马夹_",
  "九阳": "Joyoung/九阳JYF-40FS18智能家用电饭煲4l电饭锅正品2-3-4-5-6人_九阳豆浆机家用全自动多功能智能煮免过滤迷你小型官方旗舰店正品_九阳净水器家用 厨房水龙头过滤器 自来水净化器滤水器直饮净水机_Joyoung/九阳KX-30J601电烤箱家用烘焙小烤箱蛋糕迷你升正品_九阳豆浆机家用全自动多功能智能免过滤煮小型迷你官方旗舰店正品_【抢】九阳烤箱家用烘焙多功能全自动小蛋糕电烤箱30升大容量正品_九阳电陶炉家用爆炒电磁炉新款茶炉智能台式光波炉官方旗舰店正品_九阳原汁机家用全自动多功能低速渣分离榨汁机小型果汁机果蔬E10_Joyoung/九阳JK-30K09电饼铛蛋糕机煎烤机烙饼机双面电饼铛正品_九阳电磁炉灶家用电池炉智能特价正品火锅新款节能小型官方旗舰店_九阳电饭煲锅小迷你型家用官方智能6旗舰店5正品4全自动1-2-3人_九阳电压力锅家用智能5L高压饭煲官方1双胆2旗舰店3-4正品5-6-8人_九阳电饭煲锅5l升家用智能1全自动2大容量3官方4旗舰店5正品6-8人_Joyoung/九阳K17-F5电热水壶开水煲烧 食品级304不锈钢 1.7升_九阳电压力锅家用智能6L高压饭煲官方1双胆2旗舰店3-4正品5-6-8人_Joyoung/九阳电陶炉H22-x3红外光波防电磁辐射家用纤薄_九阳养生壶全自动加厚玻璃电煮茶器花茶壶多功能烧水壶中药壶正品_Joyoung/九阳JYK-50P03电热水瓶家用304不锈钢烧水壶电热水壶_Joyoung/九阳JYZ-D57榨汁机家用果蔬全自动多功能小型水果果汁机_九阳破壁机料理机家用多功能全自动养生豆浆搅拌奶昔婴儿研磨辅食_Joyoung/九阳JYZ-D57榨汁机电动水果果汁机家用多功能食品料理机_九阳电炖锅紫砂煲汤锅电砂锅家用全自动炖锅电陶瓷盅煮粥预约官方_Joyoung/九阳JYF-40FS18电饭煲4l正品迷你智能4升电饭锅_九阳养生壶全自动加厚玻璃多功能电热烧水壶花茶壶煮茶器迷你正品_九阳绞肉机家用电动不锈钢全自动小型绞馅打肉碎肉机料理机多功能_Joyoung/九阳JYZ-D57榨汁机家用多功能全自动打水果炸果汁搅拌机_九阳便携式榨汁机家用迷你小型果汁机榨汁杯学生果蔬多功能摇摇杯_九阳j63a空气炸锅 新一代大容量无油低脂全自动多功能家用电炸锅_Joyoung/九阳K15-F5电热水壶开水煲烧 304不锈钢家用保温1.5L_",
  "太平鸟": "太平鸟男装2018新款男士高领毛衣山羊绒青年毛衫羊绒衫B1EB84X16_B1EB84X16太平鸟男装2018秋冬新款男士高领毛衫羊绒衫毛衣针织衫_B1EB84X16太平鸟男装 2018秋冬新款男士翻领高领毛衫毛衣针织衫_B2EB83559太平鸟男装 2018秋款时尚潮圆领套头针织衫毛衫毛衣_太平鸟男装2018冬装新款酒红色修身高领毛衣羊针织毛衫B1EB84X18_B1EB84134太平鸟男装 2018冬新款灰色潮百搭高领针织衫毛衫毛衣_B2EB84376太平鸟男装2018冬装新款卡其色修身高领毛衫针织衫毛衣_B1EB84134太平鸟男装2018秋冬新款时尚修身高领毛衣毛衫针织衫_太平鸟男装 2018秋季新款针织兔子刺绣毛衣韩版羊毛衫男B1EB83111_B1EB84134太平鸟男装 2018冬新款灰色潮百搭高领毛衣针织衫毛衫_B2AC84161太平鸟男装 2018冬季新款时尚潮黑色棒球羽绒服面包服_B1EB83313太平鸟男装 2018秋冬新款字母刺绣修身毛衣毛衫针织衫_B1EB84427太平鸟男装2018冬新款兔子刺绣圆领套头毛衣毛衫针织衫_B1EB84X18太平鸟男装2018秋冬男士酒红色高领修身毛衫毛衣针织衫_B2EB84278太平鸟男装2018秋冬新款黑色刺绣翻领高领毛衣毛衫针织_B1EB83313太平鸟男装 2018秋冬新款修身字母刺绣毛衣毛衫针织衫_B1EB84136太平鸟男装 2018秋冬新款黑色刺绣圆领毛衣针织衫毛衫_太平鸟男装18秋新藏青色刺绣字母套头毛针织衫男士毛衣B1EB83219_B2EB84278太平鸟男装2018秋冬新款时尚刺绣翻领高领毛衣毛衫针织_B1EB83513太平鸟男装2018秋冬新款修身圆领时尚潮毛衣毛衫针织衫_B2EB84376太平鸟男装2018冬装新款修身翻领高领毛衣毛衫针织衫_太平鸟男装 秋新款青年蓝色纯色长袖衬衣修身个性可拆卸袖扣衬衫_2018秋冬新款太平鸟男装连帽印花宽松卫衣针织休闲服潮BYBF84A13_B1EB84X18太平鸟男装2018秋冬新款男士修身高领毛衣毛衫针织衫_太平鸟男装 2018秋季新款酒红色衬衣韩版翻领字母刺绣长袖衬衫潮_太平鸟女装旗艦店官方2018秋季新款常规款女毛针织衫A4EB74324_B1EB84X13太平鸟男装2018秋冬款灰色韩版修身套头毛衫针织衫毛衣_B2BC83453太平鸟男装 2018秋装新款红色联名款刺绣立领夹克外套_BYBF84A21太平鸟男装米奇联名款2018冬季新款圆领针织休闲服卫衣_",
  "蒙牛": "蒙牛学生奶粉高锌高钙女高中生儿童补钙益智青少年营养冲饮小条装_蒙牛奶粉金装中老年多维高钙奶粉900g2罐无蔗糖成人老年人牛奶粉_蒙牛中老年人奶粉高钙营养中老年奶粉成独小包装配方条装/2袋装_蒙牛金装中老年多维高钙奶粉900g*2罐 中老年人补钙成人牛奶粉_蒙牛中老年高钙奶粉金装多维400g*6袋成人男女士老人营养牛奶粉_蒙牛奶粉全脂甜成人全家早餐营养青少年女士学生儿童奶粉400g*2袋_蒙牛中老年多维高钙奶粉400g*5袋装 中老年营养奶粉冲饮早餐牛奶_蒙牛未来星儿童成长配方奶粉学生奶粉果蔬奶粉益生菌奶粉盒装400g_蒙牛金装学生多维高钙高锌奶粉900g*2罐 青少年儿童补钙牛奶粉_蒙牛奶粉中老年多维高钙奶粉400g*5袋含亚油酸独立小包装_蒙牛纯甄常温酸牛奶200gx24盒酸奶 中粮我买网直供多仓急速发货_",
  "全棉时代": "全棉时代婴儿纯棉柔巾 新生儿非湿纸巾 宝宝干湿两用 100抽6包_全棉时代袋装加厚棉柔巾便携装一次性洗脸巾100抽*6包_全棉时代婴儿棉柔巾 宝宝干湿两用巾6包/提x6提_全棉时代婴儿纯棉柔巾 宝宝干湿两用新生儿非湿纸巾 24包_全棉时代婴儿湿巾 新生儿宝宝湿巾80片/袋X16袋_全棉时代纯棉婴儿纱布浴巾 新生儿6层加厚毛巾被 儿童宝宝盖毯_全棉时代官方旗舰店新生儿超柔纱布口水巾小方巾婴儿夏天全棉时代_全棉时代纯棉加大纱布浴巾 新生儿童加厚毛巾被婴儿透气z_全棉时代官方旗舰店新生儿超柔纱布口水巾小方巾婴儿夏天全棉时代_全棉时代毛巾婴儿 宝宝手帕 纯棉纱布口水巾小方巾 超柔软6条装_全棉时代纯棉婴儿纱布浴巾 新生儿童加厚毛巾被加大透气z_全棉时代纯棉新生儿纱布浴巾95cm+洗澡手帕 宝宝大毛巾被婴儿巾_全棉时代婴儿毛巾 宝宝手帕 纯棉纱布口水巾小方巾 超柔软6条装_全棉时代棉柔巾婴儿抽纸巾干湿两用一次性洗脸巾宝宝擦pp纯棉纸巾_",
  "七匹狼": "七匹狼西裤 中青年男士时尚商务休闲无褶西裤长裤 男装正品长裤_七匹狼户外运动青年男士时尚针织立领印花防泼水拉链压胶开衫卫衣_七匹狼男装休闲裤2018秋季新款商务休闲男士直筒长裤中年男士裤子_七匹狼长袖T恤2018秋季新款中年爸爸翻领男士polo衫条纹商务男装_七匹狼男装休闲裤时尚商务简约休闲青年男士宽松直筒秋季新款长裤_",
  "雀巢": "雀巢咖啡1+2原味15g*100方包3合1速溶咖啡粉餐饮简易包装1.5kg_送电动搅拌杯雀巢原味咖啡1+2三合一速溶咖啡粉15g*100条礼盒装_雀巢怡养奶粉 中老年高钙配方无蔗糖成人老人营养奶粉850g*2罐装_送杯Nestle雀巢咖啡1+2原味三合一速溶咖啡粉盒装100条装1500g_雀巢全脂高钙奶粉全家营养奶粉家庭经济装加量550g *2袋装_雀巢橙C 果维C+甜橙味 冲饮速溶橙汁果汁粉固体饮料整箱12袋_包邮雀巢咖啡伴侣奶球50颗/袋雀巢伴侣植脂末奶精球液体_雀巢咖啡1+2特浓三合一速溶咖啡1170g/ 90条*13g礼盒装咖啡_雀巢金牌咖啡瑞士进口无糖冻干咖啡粉速溶纯黑咖啡100g×2瓶装_送杯勺雀巢咖啡经典1+2原味三合一速溶咖啡粉15g*100条包装1500g_官方授权雀巢咖啡1+2奶香味特浓咖啡15g*30条*2盒60条组合装_",
  "魅族": "Meizu/魅族魅族V8全面屏 双卡双待4G全网通学生官方新品手机全新机_现货速发/魅族魅蓝 S6 全面屏指纹识别官方旗舰店全网通正品智能手机_魅族16X【现货当天发 套餐0元购】Meizu/魅族16 x全面屏手机16_顺丰包邮 12期分销 Meizu/魅族16 x全新品正品旗舰4G智能双卡双待全面屏手机现货 骁龙845魅族16x新品手机_Meizu/魅族魅蓝6t正品全网通全面屏学生老年人智能机note魅族手机_魅蓝s6现货【送礼包】原装正品Meizu/魅族魅蓝 S6手机魅族s6_[分期免息]Meizu/魅族魅族M15 全网通4G全面屏指纹智能手机官方旗舰店正品15 16thplus note6_✅魅族16X现货【壕礼0元送】Meizu/魅族16 x 全面屏全网通智能手机官方旗舰店正品16th plus 16p新款官网正品_",
  "tcl": "TCLL40F3301B 40寸液晶电视机超高清家用卧室平板小英寸官方彩电_TCL55V2 55英寸4K全金属超薄高清人工智能网络平板液晶大电视机_?新品TCL55V2 55英寸人工智能4K高清超薄全金属智能网络电视_TCLL40F3301B 电视机40英寸液晶电视机高清老人平板普通小彩电42_TCL50V2 50英寸4K全金属超薄高清人工智能网络平板液晶大电视机_TCL32L2F 32吋高清智能WIFI网络平板LED液晶电视机32英寸特价_TCL55A880C 55英寸4K曲面超薄高清人工智能网络液晶曲屏电视机_TCLL40F3301B 小电视机 40英寸高清液晶特价平板32窄边usb视频42_TCL49A860U 49英寸4K金属超薄高清人工智能网络平板液晶电视机_TCLL32F3301B 32英寸小电视机蓝光高清彩电家用液晶电视特价卧室_TCL50L2 50吋4K高清智能WIFI网络平板LED液晶电视机50英寸特价_?新品TCL50V2 50英寸人工智能4K高清超薄全金属智能网络电视 49_TCL50L2 50英寸4K超高清智能HDR网络WIFI金属平板液晶大电视机_TCLL40F3301B 40英寸高清蓝光解码USB播放LED液晶平板电视32 39_TCL55A880C 55英寸WIFI无线曲面超薄高清人工智能4k网络遥控电视_TCL55V2 55英寸4K超薄高清人工智能WiFi网络液晶平板大电视机_TCLL32F3301B 32英寸液晶电视机32吋特价高清彩电LED平板小电视_TCL65Q2M 65英寸4K超薄无边框全面屏高清智能网络平板液晶电视机_TCL43V2 43英寸 4K超高清智能语音网络液晶wifi电视机平板彩电42_?新品TCL50L2 50英寸4K超清全新高画质防蓝光护眼智能网络电视_TCLD32A810 32吋高清智能WIFI网络平板LED液晶电视机32英寸_TCL65A880C 65英寸4K曲面超薄高清人工智能网络液晶曲屏电视机_TCL32L2F 32英寸高清智能WIFI网络安卓20核平板LED液晶电视机30_?TCL65T3M 65英寸4K超薄曲面全面屏高清人工智能网络液晶电视机_TCL50L2 50英寸LED平板液晶电视机4k超高清智能wifi官方旗舰店_TCL55A880U 55英寸4K金属超薄高清人工智能网络平板液晶电视机_TCL40L2F 40英寸高清液晶电视机智能WIFI网络平板LED-20核-特价_TCL43L2F 43英寸高清智能WIFI网络液晶电视机旗舰店同仓大40/42_TCL55Q960C 55英寸原色量子点超薄4K曲面HDR人工智能网络电视_",
  "oppo": "OPPO闪充原装充电器R17R9S R11plus R15A79数据线正品FlndX快充头_宝仕利Findx钢化膜全屏Find X弧边全覆盖玻璃膜手机防爆水凝膜oppo防摔耐刮防指纹全吸附超薄抗蓝光_宝仕利oppofindx钢化软膜水凝膜find x手机贴膜全屏覆盖背膜极光前后全包边防指纹无白边防爆防摔全透明吸附_新品oppofind x手机壳findX牛皮套高档真皮FIND X保护套防摔兰博基尼版个性创意软牛皮男女潮升降全包外壳薄_oppor9splus r11屏幕总成r11plus r9s r9sk手机内外屏原装带框_",
  "良品铺子": "良品铺子元气食足坚果礼盒1438g混合干果组合零食大礼包生日礼物_良品铺子食食有爱礼盒1149g坚果大礼包零食混合干果送礼_生日大礼包一箱好吃的休闲生日良品铺子送零食三只松鼠女友组合装_零食大礼包一箱好吃的休闲零食良品铺子送女友三只松鼠生日组合装_零食大礼包一箱好吃的休闲零食良品铺子送女友三只松鼠生日组合装_零食大礼包一箱好吃的休闲零食良品铺子送女友三只松鼠生日组合装_零食大礼包一箱好吃的休闲零食良品铺子送女友三只松鼠生日组合装_零食大礼包一箱好吃的休闲零食良品铺子送女友生日组合装_旗舰店零食大礼包送女友混装组合良品铺子休闲食品小吃混合_零食大礼包一箱好吃的休闲零食良品铺子送女友生日组合装_零食大礼包一箱好吃的休闲零食良品铺子送女友三只松鼠生日组合装_",
  "vivo": "vivox23手机壳男防摔x23手机壳vivox23潮款手机套网红金属步步高x23全包边保护套限量版x23硅胶手机壳套抖音_vivox9钢化膜x7全屏覆盖X6a原装ViVo护眼抗蓝光x9s防指纹plus手机贴膜vivi全包边d防摔i玻璃透明l_vivo耳机原装正品x7 x9s x20 plus x21手机专用入耳式耳塞式原厂_适用步步高vivox9 x7plus x6 x5pro手机屏幕总成显示内外x20 y67_"
}
var types_class = [
  ["点读笔", "玩具", "绘画本", "英氏", "全棉时代", "好奇", "贝亲", "巴拉巴拉", "可优比"],
  ["百雀羚", "玉兰油", "安奈儿",],
  ["优衣库", "运动裤", "波司登", "耐克", "羽绒服", "卫衣", "马克华菲", "裂帛", "花花公子", "美特斯邦威", "森马", "杰克琼斯", "思莱德", "太平鸟", "七匹狼", "裂帛"],
  ["良品铺子", "百草味", "三只松鼠", "海底捞", "周黑鸭", "大益", "伊利", "五谷磨房", "雀巢", "蒙牛"],
  ["格力", "史密斯", "创维", "三星", "vivo", "荣耀", "小米手机", "华为", "飞科", "飞利浦", "长虹", "西门子", "苏泊尔", "老板电器", "美的", "海尔", "海信", "格兰仕", "松下", "夏普", "九阳", "oppo", "tcl", "魅族"],
  ["预留1","全部"]
]
//点读笔    玩具    儿童绘画本    英氏    全棉时代    好奇    贝亲    巴拉巴拉    可优比    百雀羚    玉兰油    安奈儿    优衣库    运动裤    波司登    耐克    羽绒服    卫衣    马克华>菲    裂帛    花花公子    美特斯邦威    森马    杰克琼斯    思莱德    太平鸟    七匹狼    裂帛    良品铺子    百草味    三只松鼠    海底捞    周黑鸭    大益    伊利    五谷磨房    雀巢    蒙牛    格力    史密斯    创维    三星    vivo    荣耀    小米手机    华为    飞科    飞利浦    长虹    西门子    苏泊尔    老板电器    美的    海尔    海信    格兰仕    松下    夏普    九阳    oppo    tcl    魅族