main.robot

*** Settings ***
Library     NewLibrary
Library     Selenium2Library
Test Setup      get config

*** Variables ***
${keyword}     "烤箱"
${fpath}     /tmp/goods.log

*** Keywords ***
get config
    log     开始获取配置
    set suite variable     ${config}       config

write
    [Arguments]    ${fpath}    ${gid}
    writeGood    ${fpath}    ${gid}

scrab
    :FOR    ${i}    IN RANGE    0    44
        \    write    /tmp/tb.log    J_Itemlist_Pic_577383278492
        \    ${gid}    execute javascript    return document.getElementsByClassName('J_ItemPic img')[${i}].id
        \    write    ${fpath}    ${gid}
        execute javascript    document.getElementsByClassName('J_Ajax num icon-tag')[0].click()

fetch goods
    Go To    https://s.taobao.com/search?q=phone
    sleep    15
    :FOR    ${pos}    IN RANGE    0    100
    \    scrab
    \    sleep    3



*** Test Cases ***
Test
    Open Browser    https://s.taobao.com/search?q=phone    chrome
    sleep    15
    fetch goods
