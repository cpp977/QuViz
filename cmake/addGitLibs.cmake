include(ExternalProject)

set(GIFANIM_ROOT ${CMAKE_BINARY_DIR}/thirdparty/gifanim)
set(GIFANIM_INCLUDE_DIR ${GIFANIM_ROOT}/src/gifanim)

ExternalProject_Add(
        gifanim
        PREFIX ${GIFANIM_ROOT}
        GIT_REPOSITORY "https://github.com/cpp977/gifanimcplusplus.git"
        GIT_SUBMODULES_RECURSE ON
        GIT_SHALLOW ON
        TIMEOUT 10
#        UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        UPDATE_COMMAND ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        BUILD_IN_SOURCE ON
        LOG_BUILD ON
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
        LOG_MERGED_STDOUTERR ON
        USES_TERMINAL_DOWNLOAD ON
)

# set(VIVID_ROOT ${CMAKE_BINARY_DIR}/thirdparty/vivid)
# set(VIVID_INCLUDE_DIR ${VIVID_ROOT}/src/vivid)

# ExternalProject_Add(
#         vivid
#         PREFIX ${VIVID_ROOT}
#         GIT_REPOSITORY "https://github.com/gurki/vivid.git"
#         GIT_SHALLOW ON
#         TIMEOUT 10
# #        UPDATE_COMMAND ${GIT_EXECUTABLE} pull
#         UPDATE_COMMAND ""
# #        CONFIGURE_COMMAND ""
#         CMAKE_ARGS "-DCMAKE_PREFIX_PATH=/home/user/__LIBS__/json" "-DCMAKE_PREFIX_PATH=/home/user/__LIBS__/glm/cmake/glm"
# #        BUILD_COMMAND ""
# #        INSTALL_COMMAND ""
#         LOG_DOWNLOAD ON
#         LOG_MERGED_STDOUTERR ON
#         USES_TERMINAL_DOWNLOAD ON
# )

