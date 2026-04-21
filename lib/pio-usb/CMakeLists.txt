# Search for all source files in the current directory
# and save the names to the DIR_USB_SRCS variable
aux_source_directory(. DIR_USB_SRCS)

# Generate link library
add_library(pio-usb ${DIR_USB_SRCS})

# Add the standard include files to the build
target_include_directories(pio-usb PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

pico_generate_pio_header(pio-usb ${CMAKE_CURRENT_LIST_DIR}/usb_tx.pio)
pico_generate_pio_header(pio-usb ${CMAKE_CURRENT_LIST_DIR}/usb_rx.pio)

target_link_libraries(pio-usb PUBLIC 
    pico_stdlib
    pico_multicore
    hardware_pio
    hardware_dma
  )
