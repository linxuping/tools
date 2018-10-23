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
    [Arguments]    ${keyword}    ${page}    ${pos}
    log     ${config}
    Go To    https://pub.alimama.com/promo/search/index.htm?q=${keyword}&perPageSize=100&dpyhq=1&toPage=${page}&queryType=0&sortType=9
    sleep    3
    ${len}    execute javascript    return $('.block-search-box').length
    : FOR    ${i}    IN RANGE    1    ${len}
    \    Continue For Loop If    ${i}<${pos}
    \    execute javascript    document.documentElement.scrollTop=${i}00
    \    log    '.block-search-box:nth-child(${i}) .integer'
    \    ${title}    execute javascript    return $('.block-search-box:nth-child(${i}) .content-title').text()
    \    ${quanter}    execute javascript    return $('.block-search-box:nth-child(${i}) .money span')[0].innerHTML
    \    Continue For Loop If    ${quanter}<5
    \    ${integer}    execute javascript    return $('.block-search-box:nth-child(${i}) .integer')[0].innerHTML
    \    ${decimal}    execute javascript    return $('.block-search-box:nth-child(${i}) .decimal')[0].innerHTML
    \    ${sale_count}    execute javascript    return $('.block-search-box:nth-child(${i}) .color-d span')[4].innerHTML
    \    Continue For Loop If    ${sale_count}<10
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
    \    sleep    1
    \    Click Element    dom=$('#zone-form .dropdown-menu-wrapper li')[1]
    \    sleep    1
    \    Click Button    dom=$('.mr10')[1]
    \    sleep    1
    \    execute javascript    $('.block-code li')[3].click()
    \    sleep    1
    \    ${code}    execute javascript    return $('#clipboard-target-2')[0].value
    \    writetbLog    ${keyword}    ${title}    ${quanter}    ${integer}    ${decimal}    ${sale_count}    ${img}    ${code}
    \    sleep    1
    \    execute javascript    $('.dialog-ft button')[0].click()



*** Test Cases ***
Test
    close all browsers
    Open Browser    https://pub.alimama.com/    chrome
    sleep    40
    fetch tb    美特斯邦威    2    35
    @{items}    set variable    森马    杰克琼斯    思莱德    太平鸟    七匹狼    裂帛    良品铺子    百草味    三只松鼠    海底捞    周黑鸭    大益    伊利    五谷磨房    雀巢    蒙牛    格力    史密斯    创维    三星    vivo    荣耀    小米手机    华为    飞科    飞利浦    长虹    西门子    苏泊尔    老板电器    美的    海尔    海信    格兰仕    松下    夏普    九阳    oppo    tcl    魅族
    :FOR    ${item}    IN    @{items}
    \    fetch tb    ${item}    1    0
    \    fetch tb    ${item}    2    0
    close all browsers

