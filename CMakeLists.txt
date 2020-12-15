cmake_minimum_required(VERSION 3.16)
project(def)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_definitions(-DMASLO)

# ======================================================
include_directories(./Masloriy_framework)
file(GLOB Masloriy_framework CONFIGURE_DEPENDS
        "./Masloriy_framework/*.h"
        "./Masloriy_framework/*.cpp"
        )

# ======================================================


add_executable(def main.cpp)
add_executable(week1 "white_belt/week 1/part2.cpp")
add_executable(minimal_string "white_belt/week 1/minimal_string.cpp")
add_executable(uravnenie "white_belt/week 1/uravnenie.cpp")


add_executable(maksimizator "white_belt/week 2/maksimizator.cpp")
add_executable(pieriemieshchieniie-strok "white_belt/week 2/pieriemieshchieniie-strok.cpp")
add_executable(razvorot-posliedovatiel-nosti "white_belt/week 2/razvorot-posliedovatiel-nosti.cpp")
add_executable(004-sriedniaia-tiempieratura "white_belt/week 2/004-sriedniaia-tiempieratura.cpp")
add_executable(005-ochieried "white_belt/week 2/005-ochieried.cpp")
add_executable(006-iezhiemiesiachnyie-diela "white_belt/week 2/006-iezhiemiesiachnyie-diela.cpp")

add_executable(007-anaghrammy "white_belt/week 2/007-anaghrammy.cpp")

add_executable(008-spravochnik-stolits "white_belt/week 2/008-spravochnik-stolits.cpp")

add_executable(009-avtobusnyie-ostanovki-1 "white_belt/week 2/009-avtobusnyie-ostanovki-1.cpp")

add_executable(010-avtobusnyie-ostanovki-2 "white_belt/week 2/010-avtobusnyie-ostanovki-2.cpp")

add_executable(011-kolichiestvo-unikal-nykh-strok "white_belt/week 2/011-kolichiestvo-unikal-nykh-strok.cpp")

add_executable(012-mnozhiestvo-znachienii-slovaria "white_belt/week 2/012-mnozhiestvo-znachienii-slovaria.cpp")

add_executable(013-sinonimy "white_belt/week 2/013-sinonimy.cpp")

add_executable(014-avtobusnyie-ostanovki-3 "white_belt/week 2/014-avtobusnyie-ostanovki-3.cpp")

add_executable(015-sortirovka-tsielykh-chisiel-po-moduliu "white_belt/week 3/001-sortirovka-tsielykh-chisiel-po-moduliu.cpp")

add_executable(016-sortirovka-biez-uchiota-rieghistra "white_belt/week 3/002-sortirovka-biez-uchiota-rieghistra.cpp")

add_executable(003-otsortirovannyie-stroki "white_belt/week 3/003-otsortirovannyie-stroki.cpp")

add_executable(004-imiena-i-familii-1 "white_belt/week 3/004-imiena-i-familii-1.cpp")

add_executable(005-imiena-i-familii-2 "white_belt/week 3/005-imiena-i-familii-2.cpp")

add_executable(reading reading.cpp)

add_executable(006-stroka "white_belt/week 3/006-stroka.cpp")

add_executable(007-imiena-i-familii-3 "white_belt/week 3/007-imiena-i-familii-3.cpp")

add_executable(notes "white_belt/week 4/notes.cpp")

add_executable(001-struktura-lecturetitle "white_belt/week 4/001-struktura-lecturetitle.cpp")

add_executable(image-weight "white_belt/week 4/notes/image-weight.cpp")

add_executable(002-obratimaia-funktsiia "white_belt/week 4/002-obratimaia-funktsiia.cpp")

add_executable(003-obratimaia-funktsiia-s-umnozhieniiem-i-dielieniiem "white_belt/week 4/003-obratimaia-funktsiia-s-umnozhieniiem-i-dielieniiem.cpp")

add_executable(part1 "white_belt/week 4/005-rabota-s-failami/part1.cpp")

add_executable(part2 "white_belt/week 4/005-rabota-s-failami/part2.cpp")

add_executable(006-vyvod-s-tochnost-iu "white_belt/week 4/006-vyvod-s-tochnost-iu/006-vyvod-s-tochnost-iu.cpp")

add_executable(solution "white_belt/week 4/007-chtieniie-i-vyvod-tablitsy/solution.cpp")

add_executable(008-solution "white_belt/week 4/008-spisok-studientov/008-solution.cpp")

add_executable(009-solution "white_belt/week 4/009-klass-rational/009-solution.cpp")

add_executable(010-solution "white_belt/week 4/010-funktsiia-ensureequal/010-solution.cpp")

add_executable(011-iskliuchieniia-v-klassie-rational "white_belt/week 4/011-iskliuchieniia-v-klassie-rational/011-iskliuchieniia-v-klassie-rational.cpp")

add_executable(012-kal-kuliator-obyknoviennykh-drobiei "white_belt/week 4/012-kal-kuliator-obyknoviennykh-drobiei/012-kal-kuliator-obyknoviennykh-drobiei.cpp")

add_executable(013-rabota-s-siervierom-vriemieni "white_belt/week 4/013-rabota-s-siervierom-vriemieni/013-rabota-s-siervierom-vriemieni.cpp")

add_executable(final white_belt/final/final.cpp)

add_executable(001-summirovaniie-matrits yellow_belt/week_1/001-summirovaniie-matrits/001-summirovaniie-matrits.cpp)

add_executable(002-sriedniaia-tiempieratura-2 yellow_belt/week_1/002-sriedniaia-tiempieratura-2/002-sriedniaia-tiempieratura-2.cpp)

add_executable(003-massa-blokov yellow_belt/week_1/003-massa-blokov/003-massa-blokov.cpp)

add_executable(004-uproshchaiem-opierator-sravnieniia yellow_belt/week_1/004-baza-rieghionov/004-baza-rieghionov.cpp)

add_executable(005-triekier-zadach yellow_belt/week_1/005-triekier-zadach/005-triekier-zadach.cpp)

add_executable(006-vsio-v-kvadrat yellow_belt/week_1/006-vsio-v-kvadrat/006-vsio-v-kvadrat.cpp)

add_executable(007-ssylka-na-eliemient yellow_belt/week_1/007-ssylka-na-eliemient/007-ssylka-na-eliemient.cpp)

add_executable(unit_test_framework yellow_belt/week_2/!001-unit_test_framework/unit_test_framework.cpp)

add_executable(unit_test_framework_week_3 yellow_belt/week_3/unit_test_framework/unit_test_framework_week_3.cpp)

add_executable(001-diekompozitsiia-proghrammy yellow_belt/week_2/001-diekompozitsiia-proghrammy/001-diekompozitsiia-proghrammy.cpp)

add_executable(002-tiesty-dlia-funktsii-getdistinctrealrootcount yellow_belt/week_2/002-tiesty-dlia-funktsii-getdistinctrealrootcount/002-tiesty-dlia-funktsii-getdistinctrealrootcount.cpp)

add_executable(003-tiesty-dlia-klassa-person yellow_belt/week_2/003-tiesty-dlia-klassa-person/003-tiesty-dlia-klassa-person.cpp)

add_executable(004-tiesty-dlia-klassa-rational yellow_belt/week_2/004-tiesty-dlia-klassa-rational/004-tiesty-dlia-klassa-rational.cpp)

add_executable(005-tiesty-dlia-funktsii-ispalindrom yellow_belt/week_2/005-tiesty-dlia-funktsii-ispalindrom/005-tiesty-dlia-funktsii-ispalindrom.cpp)


# ======================================================
set(folder_path yellow_belt/week_3/000-project-organization)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week_3_000 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_3/001-riealizovat-funktsii-obiavliennyie-v-zagholovochnom-failie)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week_3_001 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_3/002-riealizovat-klass-obiavliennyi-v-zagholovochnom-failie)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week_3_002 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_3/003-napisat-obiavlieniie-klassa)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week_3_003 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_3/004-diekompozitsiia-proghrammy-2)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week_3-004 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_4/001-chast-viektora)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-4-001 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_4/002-chast-mnozhiestva)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-4-002 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_4/003-razbiieniie-na-slova)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-4-003 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_4/004-udalieniie-povtorov)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-4-004 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_4/005-pieriebor-pieriestanovok)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-4-005 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_4/006-diemoghrafichieskiie-pokazatieli)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-4-006 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_4/007-sortirovka-sliianiiem)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-4-007 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_4/008-poisk-blizhaishiegho-eliemienta)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-4-008 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_4/009-imiena-i-familii-4)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-4-009 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_4/010-gruppirovka-strok-po-priefiksu)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-4-010 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_4/011-postroieniie-arifmietichieskogho-vyrazhieniia)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-4-011 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_5/000)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-5-000 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_5/001-nasliedovaniie-svoimi-rukami)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-5-001 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path sample)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(sample ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_5/002-otpravka-uviedomlienii)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-5-002 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/week_5/003-nabor-fighur)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(week-5-003 ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/kursovoi-proiekt)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(kursovoi-proiekt ${project_files} ${Masloriy_framework})
# ======================================================
set(folder_path yellow_belt/course_project_yellow_solution)
file(GLOB project_files CONFIGURE_DEPENDS
        "${folder_path}/*.h"
        "${folder_path}/*.cpp"
        )
add_executable(course_project_yellow_solution ${project_files} ${Masloriy_framework})
# ======================================================
