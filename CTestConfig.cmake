set(CTEST_PROJECT_NAME "ninja")

# See "Who needs daylight savings time, anyway?" here: http://www.kitware.com/blog/home/post/77
set(CTEST_NIGHTLY_START_TIME "3:00:00 UTC")

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "my.cdash.org")
set(CTEST_DROP_LOCATION "/submit.php?project=ninja")
set(CTEST_DROP_SITE_CDASH TRUE)
