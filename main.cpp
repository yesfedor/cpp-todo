#include <crow.h>
#include <vector>
#include <string>

struct Todo {
    int id;
    std::string text;
    bool done;
};

int main() {
    crow::SimpleApp app;
    std::vector<Todo> todos = {
        {1, "Купить молоко", false},
        {2, "Настроить C++ сервер", true}
    };
    int next_id = 3;

    // API для получения списка
    CROW_ROUTE(app, "/api/todos")
    ([&]() {
        crow::json::wvalue todo_list;
        for (size_t i = 0; i < todos.size(); i++) {
            todo_list[i]["id"] = todos[i].id;
            todo_list[i]["text"] = todos[i].text;
            todo_list[i]["done"] = todos[i].done;
        }
        
        crow::response res(todo_list);
        res.add_header("Access-Control-Allow-Origin", "*"); // Разрешаем фронтенду доступ
        return res;
    });

    // API для добавления
    CROW_ROUTE(app, "/api/todos").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400);

        todos.push_back({next_id++, body["text"].s(), false});
        
        crow::response res(201);
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    // Обработка Preflight запросов (OPTIONS) — важно для CORS при POST запросах
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