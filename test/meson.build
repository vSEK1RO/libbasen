gtest_dep = dependency('gtest', main: true)

test_exe = executable(
    'test_exe',
    'hex.cpp',
    'baseN.cpp',
    'base58.cpp',
    'base64.cpp',
    'Exception.cpp',
    'hash/sha256.cpp',
    dependencies: [basen_dep, gtest_dep],
)

test('lib', test_exe)
