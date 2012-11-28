#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/IDE.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/IDE.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/pic_init.o ${OBJECTDIR}/_ext/1472/interface_register.o ${OBJECTDIR}/_ext/1472/fct_ide.o ${OBJECTDIR}/_ext/1472/spi.o ${OBJECTDIR}/_ext/1472/user.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/pic_init.o.d ${OBJECTDIR}/_ext/1472/interface_register.o.d ${OBJECTDIR}/_ext/1472/fct_ide.o.d ${OBJECTDIR}/_ext/1472/spi.o.d ${OBJECTDIR}/_ext/1472/user.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/pic_init.o ${OBJECTDIR}/_ext/1472/interface_register.o ${OBJECTDIR}/_ext/1472/fct_ide.o ${OBJECTDIR}/_ext/1472/spi.o ${OBJECTDIR}/_ext/1472/user.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
Device=PIC18F6722
ProjectDir=/home/blobby/ProgC/lecteur_cd/Code_IDE/IDE.X
ConfName=default
ImagePath=dist/default/${IMAGE_TYPE}/IDE.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
ImageDir=dist/default/${IMAGE_TYPE}
ImageName=IDE.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

.build-conf:  .pre ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/IDE.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: []"
	@
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=18F6722
MP_PROCESSOR_OPTION_LD=18f6722
MP_LINKER_DEBUG_OPTION= -u_DEBUGCODESTART=0x1fd30 -u_DEBUGCODELEN=0x2d0 -u_DEBUGDATASTART=0xeef -u_DEBUGDATALEN=0x10
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"/opt/microchip/mplabc18/v3.40/h" -I"/home/blobby/ProgC/lecteur_cd/Code_IDE/h" -ml -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/main.o   ../main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/pic_init.o: ../pic_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/pic_init.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"/opt/microchip/mplabc18/v3.40/h" -I"/home/blobby/ProgC/lecteur_cd/Code_IDE/h" -ml -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/pic_init.o   ../pic_init.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/pic_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/pic_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/interface_register.o: ../interface_register.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/interface_register.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"/opt/microchip/mplabc18/v3.40/h" -I"/home/blobby/ProgC/lecteur_cd/Code_IDE/h" -ml -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/interface_register.o   ../interface_register.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/interface_register.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/interface_register.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/fct_ide.o: ../fct_ide.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/fct_ide.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"/opt/microchip/mplabc18/v3.40/h" -I"/home/blobby/ProgC/lecteur_cd/Code_IDE/h" -ml -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/fct_ide.o   ../fct_ide.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/fct_ide.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/fct_ide.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/spi.o: ../spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/spi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"/opt/microchip/mplabc18/v3.40/h" -I"/home/blobby/ProgC/lecteur_cd/Code_IDE/h" -ml -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/spi.o   ../spi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/user.o: ../user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/user.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"/opt/microchip/mplabc18/v3.40/h" -I"/home/blobby/ProgC/lecteur_cd/Code_IDE/h" -ml -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/user.o   ../user.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/user.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/user.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"/opt/microchip/mplabc18/v3.40/h" -I"/home/blobby/ProgC/lecteur_cd/Code_IDE/h" -ml -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/main.o   ../main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/pic_init.o: ../pic_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/pic_init.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"/opt/microchip/mplabc18/v3.40/h" -I"/home/blobby/ProgC/lecteur_cd/Code_IDE/h" -ml -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/pic_init.o   ../pic_init.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/pic_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/pic_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/interface_register.o: ../interface_register.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/interface_register.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"/opt/microchip/mplabc18/v3.40/h" -I"/home/blobby/ProgC/lecteur_cd/Code_IDE/h" -ml -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/interface_register.o   ../interface_register.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/interface_register.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/interface_register.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/fct_ide.o: ../fct_ide.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/fct_ide.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"/opt/microchip/mplabc18/v3.40/h" -I"/home/blobby/ProgC/lecteur_cd/Code_IDE/h" -ml -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/fct_ide.o   ../fct_ide.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/fct_ide.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/fct_ide.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/spi.o: ../spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/spi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"/opt/microchip/mplabc18/v3.40/h" -I"/home/blobby/ProgC/lecteur_cd/Code_IDE/h" -ml -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/spi.o   ../spi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/user.o: ../user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/user.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"/opt/microchip/mplabc18/v3.40/h" -I"/home/blobby/ProgC/lecteur_cd/Code_IDE/h" -ml -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/user.o   ../user.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/user.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/user.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/IDE.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    /opt/microchip/mplabx/mpasmx/LKR/18f6722_g.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "/opt/microchip/mplabx/mpasmx/LKR/18f6722_g.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"$(BINDIR_)$(TARGETBASE).map" -l"/opt/microchip/mplabc18/v3.40/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_ICD3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}/../lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/IDE.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/IDE.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   /opt/microchip/mplabx/mpasmx/LKR/18f6722_g.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "/opt/microchip/mplabx/mpasmx/LKR/18f6722_g.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"$(BINDIR_)$(TARGETBASE).map" -l"/opt/microchip/mplabc18/v3.40/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}/../lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/IDE.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif

.pre:
	@echo "--------------------------------------"
	@echo "User defined pre-build step: []"
	@
	@echo "--------------------------------------"

# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
