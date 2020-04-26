include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES   	conv.c
					dist.c
					erfunc.c
					hsfft.c
          lls.c
					matrix.c
					pdist.c
					real.c
					regression.c
					stats.c
                    )

set(HEADER_FILES   conv.h
          cregres.h
					dist.h
					erfunc.h
					hsfft.h
          lls.h
					matrix.h
					pdist.h
					real.h
					regression.h
					stats.h
                    )

add_library(cregreslib STATIC ${SOURCE_FILES} ${HEADER_FILES})

set_property(TARGET cregreslib PROPERTY FOLDER "lib")

target_include_directories(cregreslib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
