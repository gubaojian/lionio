use actix_web::{get, web, App, HttpServer, Responder};

#[get("/hellogreet")]
async fn greet(name: web::Path<String>) -> impl Responder {
    format!("Hello word greet!")
}

#[actix_web::main] // or #[tokio::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| {
        App::new()
            .route("/hello", web::get().to(|| async { "Hello World!" }))
            .service(greet)
    })
    .bind(("127.0.0.1", 8080))?
    .run()
    .await
}