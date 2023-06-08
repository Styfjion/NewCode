type ReturnObj = {
    increment: () => number,
    decrement: () => number,
    reset: () => number,
}

function createCounter(init: number): ReturnObj {
    let curValue = init
    return <ReturnObj>{increment: () => ++curValue, decrement: () => --curValue, reset: () => curValue = init}
};

const counter = createCounter(5)
console.log(counter.increment())
console.log(counter.reset())
console.log(counter.decrement())
