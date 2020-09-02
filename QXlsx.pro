TARGET = QXlsx
TEMPLATE = subdirs

chartsquestions.file = chartsquestions/sat_gui.pro
CONFIG *= ordered
SUBDIRS *= QXlsx \
    HelloWorld \
    ReadColor \
    WhatType \
    WebServer \
    Pump \
    DateTime \
    IssueTest \
    TestExcel \
    chartsquestions \
    ShowConsole 

OTHER_FILES *= *.yml \
    *.md \
    .github/workflows/* \
    CMakeLists.txt 
