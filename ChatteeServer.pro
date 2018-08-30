QT -= gui
QT += core network sql

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    Server.cpp \
    Logger/Logger.cpp \
    Database/DAO.cpp \
    BusinessLayer/Binding.cpp \
    BusinessLayer/Message.cpp \
    BusinessLayer/User.cpp \
    Encryption/PassGenerator.cpp \
    Core/UserDescriptor.cpp \
    Core/Core.cpp \
    Protocol/Packet.cpp \
    Protocol/PacketHandler.cpp \
    Protocol/Packets/UserRegPacket.cpp \
    Protocol/Packets/UserAddMessPacket.cpp \
    Protocol/Packets/UserAddChatPacket.cpp \
    Protocol/Packets/UserLogPacket.cpp \
    Protocol/Packets/UserGetChatPacket.cpp \
    Protocol/Packets/UserGetBngsPacket.cpp
    #Core/UserAgent.cpp

HEADERS += \
    Server.h \
    Logger/Logger.h \
    Database/DAO.h \
    BusinessLayer/Binding.h \
    BusinessLayer/Message.h \
    BusinessLayer/User.h \
    Encryption/PassGenerator.h \
    Core/UserDescriptor.h \
    Core/Core.h \
    Protocol/Packet.h \
    Protocol/PacketHandler.h \
    Protocol/Packets/UserRegPacket.h \
    Protocol/Packets/UserAddMessPacket.h \
    Protocol/Packets/UserAddChatPacket.h \
    Protocol/Packets/UserLogPacket.h \
    Protocol/Packets/UserGetChatPacket.h \
    Protocol/Packets/UserGetBngsPacket.h
    #Core/UserAgent.h

DISTFILES += \
    database/maindb.sqlite
