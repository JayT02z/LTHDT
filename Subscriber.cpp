#include <iostream>
#include <list>
#include <string>

class ISubscriber {
public:
    virtual ~ISubscriber() {}
    virtual void Update(const std::string& video_link) = 0;
};

class YouTubeChannel {
public:
    void Attach(ISubscriber* subscriber) {
        list_subscriber_.push_back(subscriber);
    }

    void Detach(ISubscriber* subscriber) {
        list_subscriber_.remove(subscriber);
    }

    void Notify() {
        for (auto subscriber : list_subscriber_) {
            subscriber->Update(video_link_);
        }
    }

    void CreateVideo(const std::string& video_link) {
        this->video_link_ = video_link;
        Notify();
        std::cout << "A new video has been uploaded: " << video_link << "\n";
    }

    void HowManySubscribers() {
        std::cout << "There are " << list_subscriber_.size() << " subscribers in the channel.\n";
    }

private:
    std::list<ISubscriber*> list_subscriber_;
    std::string video_link_;
};

class Subscriber : public ISubscriber {
public:
    Subscriber(YouTubeChannel& channel) : channel_(channel) {
        this->channel_.Attach(this);
        std::cout << "Hi, I'm the Subscriber \"" << ++Subscriber::static_number_ << "\".\n";
        this->number_ = Subscriber::static_number_;
    }
    virtual ~Subscriber() {
        std::cout << "Goodbye, I was the Subscriber \"" << this->number_ << "\".\n";
    }

    void Update(const std::string& video_link) override {
        video_link_from_channel_ = video_link;
        PrintInfo();
    }
    void RemoveMeFromTheList() {
        channel_.Detach(this);
        std::cout << "Subscriber \"" << number_ << "\" removed from the list.\n";
    }
    void PrintInfo() {
        std::cout << "Subscriber \"" << this->number_ << "\": a new video is available --> " << this->video_link_from_channel_ << "\n";
    }

private:
    std::string video_link_from_channel_;
    YouTubeChannel& channel_;
    static int static_number_;
    int number_;
};

int Subscriber::static_number_ = 0;

void ClientCode() {
    YouTubeChannel* channel = new YouTubeChannel;
    Subscriber* subscriber1 = new Subscriber(*channel);
    Subscriber* subscriber2 = new Subscriber(*channel);
    Subscriber* subscriber3 = new Subscriber(*channel);
    Subscriber* subscriber4;
    Subscriber* subscriber5;

    channel->CreateVideo("https://youtu.be/8BTfgwE27CY");
    subscriber3->RemoveMeFromTheList();

    channel->CreateVideo("https://youtu.be/zEWSSod0zTY");
    subscriber4 = new Subscriber(*channel);

    subscriber2->RemoveMeFromTheList();
    subscriber5 = new Subscriber(*channel);

    channel->CreateVideo("https://youtu.be/Oz8RF_1eGxw");
    subscriber5->RemoveMeFromTheList();

    subscriber4->RemoveMeFromTheList();
    subscriber1->RemoveMeFromTheList();

    delete subscriber5;
    delete subscriber4;
    delete subscriber3;
    delete subscriber2;
    delete subscriber1;
    delete channel;
}

int main() {
    ClientCode();
    return 0;
}