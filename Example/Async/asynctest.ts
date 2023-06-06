const sleep = (delay) => new Promise((resolve) => setTimeout(resolve, delay))

async function g(): Promise<any> {
    console.log("g 1")
    await sleep(1000)
    console.log("g 2")
}

async function f(): Promise<any> {
    let a = g()
    console.log("f 1")
    await a
    await sleep(1000)
    console.log("f 2")
}

async function out(): Promise<any> {
    let b = f()
    console.log("start")
    await b
    console.log("finish")
}

out().then(() => {
    console.log("Success")
}).catch(err => {
    console.log(err)
})

// g 1
// f 1
// start
// g 2
// f 2
// finish
// Success

