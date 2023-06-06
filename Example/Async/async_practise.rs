use std::time::Duration;

async fn g() {
    println!("g 1");
    tokio::time::sleep(Duration::from_secs(1)).await;
    println!("g 2");
}

async fn f() {
    let a = tokio::spawn(g());
    tokio::task::yield_now().await;
    println!("f 1");
    a.await.unwrap();
    println!("f 2");
}

#[tokio::main]
async fn main() {
    f().await
}

// f 1
// g 1
// g 2
// f 2
