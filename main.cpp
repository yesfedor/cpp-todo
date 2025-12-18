#include <crow.h>
#include <string>
#include "todo.pb.h"

int main() {
    crow::SimpleApp app;

    TodoList db;

    auto* t1 = db.add_items();
    t1->set_id(1);
    t1->set_text("Купить молоко");
    t1->set_done(false);

    auto* t2 = db.add_items();
    t2->set_id(2);
    t2->set_text("Настроить Protobuf");
    t2->set_done(true);

    static int next_id = 3;

    CROW_ROUTE(app, "/api/todos")
    ([&]() {
        std::string out;
        db.SerializeToString(&out);

        crow::response res(out);
        res.add_header("Content-Type", "application/x-protobuf");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    CROW_ROUTE(app, "/api/todos").methods(crow::HTTPMethod::OPTIONS)
    ([]() {
        crow::response res(204);
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    });

    app.port(18080).multithreaded().run();
}