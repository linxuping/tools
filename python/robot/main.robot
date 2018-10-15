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
    [Arguments]    ${keyword}
    log     ${config}
    Go To    https://pub.alimama.com/promo/search/index.htm?q=${keyword}&perPageSize=100&dpyhq=1&hPayRate30=1&freeShipment=1
    sleep    5
    : FOR    ${i}    IN RANGE    1    30
    \    execute javascript    document.documentElement.scrollTop=${i}00
    \    log    '.block-search-box:nth-child(${i}) .integer'
    \    ${title}    execute javascript    return $('.block-search-box:nth-child(${i}) .content-title').text()
    \    ${quanter}    execute javascript    return $('.block-search-box:nth-child(${i}) .money span')[0].innerHTML
    \    ${integer}    execute javascript    return $('.block-search-box:nth-child(${i}) .integer')[0].innerHTML
    \    ${decimal}    execute javascript    return $('.block-search-box:nth-child(${i}) .decimal')[0].innerHTML
    \    ${sale_count}    execute javascript    return $('.block-search-box:nth-child(${i}) .color-d span')[4].innerHTML
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
    @{items}    set variable    小米手机    耐克    荣耀   华为    vivo    oppo    魅族    三星
    :FOR    ${item}    IN    @{items}
    \    fetch tb    ${item}
    @{items}    set variable    优衣库    韩都衣舍    zara    波司登    裂帛    七匹狼
    :FOR    ${item}    IN    @{items}
    \    fetch tb    ${item}
    close all browsers

