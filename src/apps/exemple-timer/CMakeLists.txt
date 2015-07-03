add_executable					(exemple main.cc)
target_link_libraries   (exemple khronos ${libraries})
install									(TARGETS exemple DESTINATION bin/apps)
