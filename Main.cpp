#include <iostream>
#include <vector>
#include <string>

class ISubscriber {
public:
    virtual void update() = 0;
    virtual void like() = 0;
    virtual void unLike() = 0;
};

class YouTubeUser {
private:
    std::vector<ISubscriber*> subscribers;

public:
    void addSubscriber(ISubscriber* subscriber) {
        subscribers.push_back(subscriber);
    }

    void removeSubscriber(ISubscriber* subscriber) {
        subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
    }

    void notifySubscribers() {
        for (ISubscriber* subscriber : subscribers) {
            subscriber->update();
        }
    }

    void uploadNewVideo() {
        std::cout << "YouTubeUser: Uploading a new video." << std::endl;
        notifySubscribers();
    }

};

class Subscriber : public ISubscriber{
private:
    std::string subscribers;

public:
    void getName() {
        std::cout << this->subscribers;
    }
    void update() override {
        std::cout << "Subscriber" << getName() <<  ": Received an update." << std::endl ;
    }

    void like() {
        std::cout << "Subscriber" << getName() << ": Like your video!" << std::endl;
    }

    void unLike() {
        std::cout << "Subscriber" << ": Unlike your video!" << std::endl;
    }
};


int main() {
    YouTubeUser user;

    Subscriber subscriber1;
    Subscriber subscriber2;

    user.addSubscriber(&subscriber1);
    user.addSubscriber(&subscriber2);

    user.uploadNewVideo();
    subscriber1.like();
    subscriber2.unLike();

    user.removeSubscriber(&subscriber1);

    return 0;
}