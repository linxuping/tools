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
    sleep    5
    Go To    https://pub.alimama.com/promo/search/index.htm?q=纸巾&perPageSize=100
    sleep    5
    : FOR    ${i}    IN RANGE    1    101
    \    log    '.block-search-box:nth-child(${i}) .integer'
    \    ${val}    execute javascript    return $('.block-search-box:nth-child(${i}) .integer')[0].innerHTML
    \    log    ${val}
    Close Browser
