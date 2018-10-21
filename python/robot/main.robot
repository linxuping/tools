main.robot

*** Settings ***
Library     NewLibrary
Library     Selenium2Library
Test Setup      get config

*** Variables ***
${test}     123

*** Keywords ***
get config
    log     开始获取配置
    set suite variable     ${config}       config

fetch tb
    [Arguments]    ${keyword}    ${page}
    log     ${config}
    Go To    https://pub.alimama.com/promo/search/index.htm?q=${keyword}&perPageSize=100&dpyhq=1&toPage=${page}&queryType=0&sortType=9
    sleep    5
    ${len}    execute javascript    return $('.block-search-box').length
    : FOR    ${i}    IN RANGE    1    ${len}
    \    execute javascript    document.documentElement.scrollTop=${i}00
    \    log    '.block-search-box:nth-child(${i}) .integer'
    \    ${title}    execute javascript    return $('.block-search-box:nth-child(${i}) .content-title').text()
    \    ${quanter}    execute javascript    return $('.block-search-box:nth-child(${i}) .money span')[0].innerHTML
    \    Continue For Loop If    ${quanter}<5
    \    ${integer}    execute javascript    return $('.block-search-box:nth-child(${i}) .integer')[0].innerHTML
    \    ${decimal}    execute javascript    return $('.block-search-box:nth-child(${i}) .decimal')[0].innerHTML
    \    ${sale_count}    execute javascript    return $('.block-search-box:nth-child(${i}) .color-d span')[4].innerHTML
    \    Continue For Loop If    ${sale_count}<3
    \    ${img}    execute javascript    return $('.block-search-box:nth-child(${i}) .pic-box img')[0].src
    \    log    ${title}
    \    log    ${quanter}
    \    log    ${integer}
    \    log    ${decimal}
    \    log    ${sale_count}
    \    log    ${img}
    \    execute javascript    $('.block-search-box:nth-child(${i}) .box-btn-group a')[0].click()
    \    sleep    2
    \    Click Button    dom=$('.dropdown-toggle')[4]
    \    sleep    2
    \    Click Element    dom=$('#zone-form .dropdown-menu-wrapper li')[1]
    \    sleep    2
    \    Click Button    dom=$('.mr10')[1]
    \    sleep    2
    \    execute javascript    $('.block-code li')[3].click()
    \    sleep    1
    \    ${code}    execute javascript    return $('#clipboard-target-2')[0].value
    \    sleep    1
    \    writetbLog    ${keyword}    ${title}    ${quanter}    ${integer}    ${decimal}    ${sale_count}    ${img}    ${code}
    \    sleep    1
    \    execute javascript    $('.dialog-ft button')[0].click()



*** Test Cases ***
Test
    close all browsers
    Open Browser    https://pub.alimama.com/    chrome
    sleep    40
    @{items}    set variable     海底捞    波司登    周黑鸭    三星    vivo    大益    伊利    五谷磨房    荣耀    耐克    百雀羚    玉兰油    小米手机    华为    羽绒服    点读笔    卫衣    预留1    马克华菲    飞科    飞利浦    长虹    贝亲    西门子    裂帛    英氏    苏泊尔    花花公子    老板电器    美的    美特斯邦威    海尔    海信    森马    格兰仕    松下    杰克琼斯    思莱德    巴拉巴拉    安奈儿    好奇    太平鸟    夏普    全棉时代    九阳    七匹狼    tcl    魅族    裂帛    oppo    雀巢    蒙牛   
    :FOR    ${item}    IN    @{items}
    \    fetch tb    ${item}    1
    \    fetch tb    ${item}    2
    \    fetch tb    ${item}    3
    \    fetch tb    ${item}    4
    \    fetch tb    ${item}    5
    close all browsers

