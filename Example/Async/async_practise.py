import asyncio


async def g():
    print("g 1")
    await asyncio.sleep(1)
    print("g 2")


async def f():
    a = asyncio.create_task(g())
    await asyncio.sleep(0) # return control to loop so task can start
    print("f 1")
    await a
    print("f 2")


async def main():
    await f()


if __name__ == '__main__':
    asyncio.run(main())

# g 1
# f 1
# g 2
# f 2
