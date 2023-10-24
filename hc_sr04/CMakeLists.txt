set(component_srcs "hc_sr04.c")

idf_component_register(SRCS "${component_srcs}"
                       INCLUDE_DIRS "."
                       REQUIRES ssd1306)
