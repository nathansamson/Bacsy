add_executable(test
                   Main
                   ConfigurationTests
                   StringUtilsTests
                   TimerStringParserTests
                   StoreIndexTests
                   ConcurrentMapTests
                   RsyncStreamTests
                   ExclusionStringParserTests
                   StringExclusionRuleBuilderTests
				   RunTypeTests
)

target_link_libraries(test gtest ${bacsy_libraries})
