class DisplayFPS {
public:
    sf::Text text;
    int historySize = 40;
    std::vector <double> historicalFPS;

    DisplayFPS() {
        text.setFont(game.CourierPrime_Regular);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color(255, 255, 255));
        text.setPosition(5, 0);
    }

    void drawFPS(sf::RenderWindow& window, sf::Clock& clock) {
        double fpsThisFrame = getFPS(clock);
        pushAndPop(fpsThisFrame);
        double fpsRollingAverage = returnRollingAverageFPS();
        text.setString("FPS: " + std::to_string(int(fpsRollingAverage)));
        window.draw(text);
    }

    void pushAndPop(double fps) {
        historicalFPS.push_back(fps);
        if (historicalFPS.size() > historySize) {
            historicalFPS.erase(historicalFPS.begin());
        }
    }

    double returnRollingAverageFPS() {
        double sum = 0;
        for (double fps : historicalFPS) {
            sum += fps;
        }
        return sum / historicalFPS.size();
    }

    double getFPS(sf::Clock& clock) {
        sf::Time timeSinceLastFrame = clock.getElapsedTime();
        clock.restart();
        return (1.0 / timeSinceLastFrame.asSeconds());
    }
};
