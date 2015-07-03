add_executable					(exemple-timer main.cc)
target_link_libraries   (exemple-timer khronos ${libraries})
install									(TARGETS exemple-timer DESTINATION bin/apps)
