#/******************************************************************************
# * Function:
# * Description:
# *
# * Input:
# * Output:
# * Return:
# * Modification history
# * ----------------------------
# * 01a, 2021.10.6, Created by ougnaij@gmail.com 
# *
# * ----------------------------
#******************************************************************************/

buildver=ver_lede

ADD_LIB=-lssl -lcrypto 
#-lwebsockets -lmbedtls -lpthread -lmbedcrypto -lmbedx509 -lcap -lcjson -lnl-tiny

# Year 2012 is the year we started.
str_version = `date "+%Y"`
PRO_VERSION = ${shell echo "$$[$(str_version)-2012]"}

# Build Month
PRO_BUILD_MON = `date "+%m"`

#IAR_2018092100 Makefile中的八进制问题
#PRO_BUILD_SEASON = $$[($(PRO_BUILD_MON)-1)/3+1]
#PRO_BUILD_SEASON_MON = $$[$(PRO_BUILD_MON)-($(PRO_BUILD_SEASON)-1)*3]

PRO_BUILD_SEASON = $$[(10\#$(PRO_BUILD_MON)-1)/3+1]
PRO_BUILD_SEASON_MON = $$[10\#$(PRO_BUILD_MON)-($(PRO_BUILD_SEASON)-1)*3]

# This is the times that send software to our client.
PRO_PATCHLEVEL = 00

# Build Date
PRO_SUBLEVEL = `date "+%d"`

CURRENT_DATE = `date "+%T %F"`
BUILD_HOUR = `date "+%H""%M"`

VERSION_FILE = inc/version.h

INC_PATH = -Iinc
BIN = ./bin
SRC = ./src
INC = ./inc
OBJ = ./obj

SOURCE = $(wildcard ${SRC}/*.c)
#SOURCE = src/main.c           \
#         src/syslog.c         \
#         src/wlan_api.c       \
#         src/interface.c      \
#         src/iw.c             \
#         src/sections.c       \
#         src/util.c           \
#         src/vendor.c         \
#         src/station.c        \
#         src/bitrate.c        \
#         src/scan.c           \
#         src/event.c          \
#         src/os_api.c         \
#         src/app_sta.c        \
#         src/app_ap.c         \
#         src/script.c         \
#         src/i2cbusses.c      \
#         src/i2cutil.c        \
#         src/smbus.c          \
#         src/usbhub.c         \
#         src/basic_auth.c     \
#         src/callback_hmos.c  \
#         src/dhcp_api.c       \
#         src/radio_api.c      \
#         src/proto.c          \
#         src/rate_api.c       \
#         src/wanlan.c         \
#         src/pca9555.c        \
#         src/att.c            \
#         src/user_man.c

OBJECT = $(patsubst %.c,${OBJ}/%.o,$(notdir ${SOURCE}))


TARGET = agent
BIN_TARGET = ${BIN}/${TARGET}
#-g -Wall -DDEBUG_VER --sysroot=${SYSROOT_PATH} 
CFLAGS =   ${INC_PATH}  -DDEBUG_VER -DPROSYS_VER

#${BIN_TARGET}: PREPARE_BUILD ${OBJECT}
${BIN_TARGET}:  PREPARE_BUILD ${OBJECT}
	@echo
	@echo Generating ${BIN_TARGET}
	$(CC) -o $@ ${OBJECT} -B ${LIB_PATH} ${ADD_LIB}
	@cp -f $@ $@_dbg
	@$(STRIP) $@

${OBJ}/%.o:${SRC}/%.c
	@echo "Build $< ..."
	@$(CC) $(CFLAGS) -o $@ -c $<

GEN_VERFILE:
	@echo Generate Version file
	@echo > $(VERSION_FILE)
	@echo "/* Automatically generated - do not edit */" >> $(VERSION_FILE)
	@echo >> $(VERSION_FILE)
	@echo "/***************************************************************************************" >> $(VERSION_FILE)
	@echo "****************************************************************************************" >> $(VERSION_FILE)
	@echo "* File        : version.h " >> $(VERSION_FILE)
	@echo "* Description : version file automatically generated." >> $(VERSION_FILE)
	@echo "* Date        : $(CURRENT_DATE)" >> $(VERSION_FILE)
	@echo "* 2021 by ougnaij@gmail.com" >> $(VERSION_FILE)
	@echo " ">> $(VERSION_FILE)
	@echo "****************************************************************************************" >> $(VERSION_FILE)
	@echo "****************************************************************************************/" >> $(VERSION_FILE)
	@echo >> $(VERSION_FILE)
	@echo -e  "#define PRO_VERSION \"$(PRO_VERSION)\"" >> $(VERSION_FILE)
	@echo -e  "#define PRO_BUILD_MON \"$(PRO_BUILD_MON)\"" >> $(VERSION_FILE)
	@echo -e  "#define PRO_BUILD_SEASON \"$(PRO_BUILD_SEASON)\"" >> $(VERSION_FILE)
	@echo -e  "#define PRO_BUILD_SEASON_MON \"$(PRO_BUILD_SEASON_MON)\"" >> $(VERSION_FILE)
	@echo -e  "#define PRO_PATCHLEVEL \"$(PRO_PATCHLEVEL)\"" >> $(VERSION_FILE)
	@echo -e  "#define PRO_SUBLEVEL \"$(PRO_SUBLEVEL)\"" >> $(VERSION_FILE)
	@echo -e  "#define BUILD_HOUR \"$(BUILD_HOUR)\"" >> $(VERSION_FILE)

	@echo >> $(VERSION_FILE)
	@echo "/* Automatically generated - do not edit */" >> $(VERSION_FILE)
	@echo >> $(VERSION_FILE)
#	@echo done.

PREPARE_BUILD:GEN_VERFILE
	@echo Building...

.PHONY:clean
clean:
	@find $(OBJ) -name *.o -exec rm -rf {} \;
	@rm -rf $(BIN_TARGET)
	@echo "Clean done"
	@echo



