host_build {
    QT_ARCH = x86_64
    QT_BUILDABI = x86_64-little_endian-lp64
    QT_TARGET_ARCH = arm64
    QT_TARGET_BUILDABI = arm64-little_endian-lp64
} else {
    QT_ARCH = arm64
    QT_BUILDABI = arm64-little_endian-lp64
}
QT.global.enabled_features = shared cross_compile c++11 c++14 c99 c11 thread future concurrent signaling_nan
QT.global.disabled_features = framework rpath appstore-compliant debug_and_release simulator_and_device build_all c++1z c++2a pkg-config force_asserts separate_debug_info static
QT_CONFIG += shared release c++11 c++14 concurrent no-pkg-config reduce_exports stl
CONFIG += shared cross_compile release
QT_VERSION = 5.14.0
QT_MAJOR_VERSION = 5
QT_MINOR_VERSION = 14
QT_PATCH_VERSION = 0
QT_GCC_MAJOR_VERSION = 6
QT_GCC_MINOR_VERSION = 3
QT_GCC_PATCH_VERSION = 1
QT_EDITION = OpenSource
