*** Settings ***
Library           Selenium2Library

*** Test Cases ***
wxtest
    Open Browser    https://wx.qq.com/    chrome
    sleep    30
    click Element    xpath=//*[@class="web_wechat_down_icon"]
    sleep    2
    : FOR    ${i}    IN RANGE    249    1000
    \    click Element    //div[@class="member ng-scope" and position()=${i}]//img
    \    log    ${i}
    \    sleep    1
    \    execute javascript    if ($('.web_wechat_tab_add').length){ $('.web_wechat_tab_add').click(); };
    \    sleep    1
    \    ${check} =    Run Keyword And Return Status    Page Should Contain Element    xpath=//*[@class="verify_text ng-pristine ng-valid"]
    \    Log    ${check}
    \    run keyword if    ${check}    Try Add User
    \    click Element    xpath=//*[@class="web_wechat_up_icon"]
    \    sleep    1
    \    click Element    xpath=//*[@class="web_wechat_down_icon"]
    \    sleep    15
    Close Browser

*** Keywords ***
Try Add User
   Log    "into "
   Input Text    xpath=//*[@class="verify_text ng-pristine ng-valid"]    早上好！
   sleep    1
   click Element    xpath=//*[@class="form_area ng-scope"]/a
   sleep    2
