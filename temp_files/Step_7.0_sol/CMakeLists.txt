# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(remote_controller)

target_sources(app PRIVATE src/main.c)

#Step 3.1 - add custom files folder
# Custom files and folders
#Step 4.0.1 add remote.c
target_sources(app PRIVATE
    src/custom_files/motor_control.c;
    src/custom_files/remote.c;
)

zephyr_library_include_directories(src/custom_files)