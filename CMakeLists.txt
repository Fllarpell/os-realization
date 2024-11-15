cmake_minimum_required(VERSION 3.29)
project(os_realization C)

set(CMAKE_C_STANDARD 23)

add_executable(os_realization
        processes-threads/threads-time/ex1.c
        processes-threads/multiforks/ex3.c
        processes-threads/simplistic-shell/ex4.c
        processes-threads/channel-subscriber/channel.c
        processes-threads/channel-subscriber/subscriber.c
        processes-threads/channel-subscriber/publisher.c
        main.c
        processes-threads/thread-struct/ex2.c
        processes-threads/prime-numbers/ex4.c
        processes-scheduling/agent-controller/agent.c
        processes-scheduling/agent-controller/controller.c
        processes-scheduling/worker-scheduler/worker.c
        processes-scheduling/worker-scheduler/scheduler.c
        input-output/keyboard-events.c
        memory-management/virtual-memory/random-password/password.c
        main.c
        memory-management/allocating-memory/ex3.c)
