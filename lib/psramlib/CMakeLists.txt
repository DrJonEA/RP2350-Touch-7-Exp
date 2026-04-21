
add_library(psramlib INTERFACE)

target_sources(
    psramlib
    INTERFACE ${CMAKE_CURRENT_LIST_DIR}/rp_pico_alloc.c
              ${CMAKE_CURRENT_LIST_DIR}/rp_pico_alloc.h
              ${CMAKE_CURRENT_LIST_DIR}/tlsf/tlsf.c
              ${CMAKE_CURRENT_LIST_DIR}/tlsf/tlsf.h
              ${CMAKE_CURRENT_LIST_DIR}/tlsf/tlsf_common.h
              ${CMAKE_CURRENT_LIST_DIR}/tlsf/tlsf_block_functions.h)

# Are we wrapping the built in alloc functions?
if (RP_PICO_ALLOC_WRAP)
    pico_wrap_function(psramlib malloc)
    pico_wrap_function(psramlib calloc)
    pico_wrap_function(psramlib realloc)
    pico_wrap_function(psramlib free)
endif ()
target_include_directories(psramlib INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(psramlib INTERFACE pico_stdlib hardware_spi hardware_gpio hardware_flash pico_flash
                                              hardware_exception hardware_sync)
