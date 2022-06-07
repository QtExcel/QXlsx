# SPDX-FileCopyrightText: (C) 2021 Daniel Nicoletti <dantti12@gmail.com>
# SPDX-License-Identifier: MIT

set(CPACK_PACKAGE_VENDOR "Daniel Nicoletti")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "QXlsx library.")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/../README.md")
set(CPACK_PACKAGE_CONTACT "Daniel Nicoletti <dantti12@gmail.com>")

if(UNIX)
  if(NOT CPACK_GENERATOR)
    set(CPACK_GENERATOR "DEB")
  endif()

  set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
  set(CPACK_STRIP_FILES 1)
  if(${CMAKE_VERSION} VERSION_GREATER "3.5")
    set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
  endif()
endif()

include(CPack)
