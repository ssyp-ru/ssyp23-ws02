# ssyp23-ws02
Мастерская №2 "640 байт хватит всем"

Компиляция
----------

Для сборки проектов понадобится:

Компилятор: SDCC версии 4.2.0 и свежее(главное, чтобы была поддержка STM8)
Утилита для прошивки контроллера: stm8flash(см. https://github.com/vdudouyt/stm8flash)
Codeblocks 20.04
Wizard для создания проектов STM8 для Codeblocks(см. https://cxem.net/ckfinder/userfiles/e00d5b39a6e3e693eab8817ee4f98283/files/codeblocks-stm8-wizard.zip)

Wizard необходимо добавить в папку с другими wizard(/usr/share/codeblocks/templates/wizard/ - для Linux)

В той же папке, открываем config.script и добавляем строчку:

`RegisterWizard(wizProject,     _T("stm8"),         _T("STM8 Project"),         _T("Embedded Systems"));`

После пункта mcs51.

Если сборка проходит под Linux, то в в папке stm8 нужно поправить 113 строчку wizard.script:

`target.AddCommandsAfterBuild(_T("packihx <$(TARGET_OUTPUT_DIR)$(TARGET_OUTPUT_BASENAME).ihx >$(TARGET_OUTPUT_DIR)$(TARGET_OUTPUT_BASENAME).hex"));`

После этого, в Codeblocks можно легко создать новый проект, добавить файлы и собрать файлы прошивок в формате .hex. Они будут лежать в bin\Release\<project_name>.hex

Прошивка осуществляется с помощью утилиты stm8flash:
`./stm8flash -c stlink -p stm8s105k4 -w <project_name>.hex`

Если, проект содержит файл image.hex - это означает, что проект использует eeprom память, например для спрайтов. Прошивка осуществляется также, как и в предыдущем случае + флаг смещения адреса:
`./stm8flash -c stlink -p stm8s105k4 -s eeprom -w image.hex`
