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

*** Test Cases ***
test
    log     ${config}
    print msg     ss
    Open Browser    https://pub.alimama.com/    chrome
    sleep    10
    Go To    https://pub.alimama.com/promo/search/index.htm?q=纸巾&perPageSize=100
    sleep    5
    : FOR    ${i}    IN RANGE    1    2
    \    log    '.block-search-box:nth-child(${i}) .integer'
    \    ${val}    execute javascript    return $('.block-search-box:nth-child(${i}) .integer')[0].innerHTML
    \    log    ${val}
    \    Click Link    dom=$('.block-search-box:nth-child(${i}) .box-btn-group a')[0]
    \    sleep    2
    \    Click Button    dom=$('.dropdown-toggle')[4]
    \    sleep    2
    \    Click Element    dom=$('#zone-form .dropdown-menu-wrapper li')[1]
    \    sleep    2
    \    Click Button    dom=$('.mr10')[1]
    \    sleep    1
    \    Click Element    dom=$('.block-code li')[3]
    \    sleep    1
    \    ${code}    execute javascript    return $('#clipboard-target-2')[0].value
