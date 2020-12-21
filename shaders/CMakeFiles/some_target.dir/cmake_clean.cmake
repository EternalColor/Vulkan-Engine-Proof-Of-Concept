file(REMOVE_RECURSE
  "/usr/share/cmake-3.19/build/*.spv"
  "CMakeFiles/some_target"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/some_target.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
