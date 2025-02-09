add_executable(test_asset_history test_asset_history.cpp
                                 ${CMAKE_SOURCE_DIR}/src/AssetHistory.cpp
                                 ${CMAKE_SOURCE_DIR}/src/Util.cpp)
target_include_directories(test_asset_history PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/extern/catch2)
add_test(NAME test_asset_history COMMAND test_asset_history)

add_executable(test_trader test_trader.cpp
                        ${CMAKE_SOURCE_DIR}/src/HistoryObserver.cpp
                        ${CMAKE_SOURCE_DIR}/src/Portfolio.cpp
                        ${CMAKE_SOURCE_DIR}/src/Asset.cpp
                        ${CMAKE_SOURCE_DIR}/src/TimeSeries.cpp
                        ${CMAKE_SOURCE_DIR}/src/Market.cpp
                        ${CMAKE_SOURCE_DIR}/src/AssetHistory.cpp
                        ${CMAKE_SOURCE_DIR}/src/Trader.cpp
                        ${CMAKE_SOURCE_DIR}/src/Util.cpp)
target_include_directories(test_trader PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/extern/catch2)
add_test(NAME test_trader COMMAND test_trader)
