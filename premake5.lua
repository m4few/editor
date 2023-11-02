THREAD_REPO = "https://github.com/m4few/c-thread-pool"

workspace("test")
configurations({ "Debug", "Release" })

os.execute("rm -rf lib")
os.execute("git clone " .. THREAD_REPO)
os.execute("mv c-thread-pool lib")

project("test")
kind("ConsoleApp")
language("C")
targetdir("bin/%{cfg.buildcfg}")

files({ "**.h", "**.c", "lib/**.c" })

filter("configurations:Debug")
defines({ "DEBUG" })
symbols("On")

filter("configurations:Release")
defines({ "NDEBUG" })
optimize("On")
