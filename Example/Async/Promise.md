# Promise

Promise自身接收一个参数为resolve或(resolve, reject)的同步函数，在这个同步函数中可以执行自己的逻辑，该函数为闭包可以捕获外界变量
1. Lee2637设置超时机制
```typescript
type Fn = (...params: any[]) => Promise<any>;

function timeLimit(fn: Fn, t: number): Fn {
    return async function (...args) {
        return new Promise((resolve, reject) => {
            fn(...args).then(resolve).catch(reject)
            setTimeout(() => reject("Time Limit Exceeded"), t)
        })
    }
};
```

2. sleep函数， setTimeout为同步方式执行，通过Promise转化为异步
```typescript
const sleep = (delay: number) => new Promise(r => setTimeout(r, delay))

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

```
