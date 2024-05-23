extern Snowflake::Application *Snowflake::create_application();

int main()
{
    auto app = Snowflake::create_application();
    app->run();
    delete app;

    return 0;
}