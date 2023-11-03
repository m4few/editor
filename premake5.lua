THREAD_REPO = "https://github.com/m4few/c-thread-pool"

workspace("editor")
configurations({ "Debug", "Release" })

os.execute("rm -rf lib")
os.execute("git clone " .. THREAD_REPO)
os.execute("mv c-thread-pool external")

project("editor")
kind("ConsoleApp")
language("C")
targetdir("bin/%{cfg.buildcfg}")

files({ "**.h", "**.c", "external/**.c", "internal/**.c" })

filter("configurations:Debug")
defines({ "DEBUG" })
symbols("On")

filter("configurations:Release")
defines({ "NDEBUG" })
optimize("On")
