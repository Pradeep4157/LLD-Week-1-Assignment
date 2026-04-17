// 02-media-lsp-isp.cpp
// Messy starter: Fat interface + LSP surprises (violates ISP + LSP)

#include <iostream>
#include <string>
#include <stdexcept>
/*
    Player is really fat interface, we need to remove some of the function and create some more

    interfacse to add these functions..

    interface segregation is done..

    in the play function there is a question of whether live stream has started or not ..



*/
using namespace std;
class Playable
{
public:
    virtual void play(const string &source) = 0;
    virtual void pause() = 0;
};
class Downloadable
{
public:
    virtual void download(const string &sourceUrl) = 0;
};
class LiveStreamable
{
public:
    virtual void streamLive(const string &url) = 0;
};
class VideoRecordable
{
public:
    virtual void record(const string &destination) = 0;
};

class AudioPlayer : public Playable, public Downloadable
{

    bool playing{false};

public:
    void play(const string &source) override
    {
        (void)source;
        playing = true;
    }
    void pause() override { playing = false; }
    void download(const string &url) override { (void)url; /* pretend */ }
    bool isPlaying() const { return playing; }
};

class CameraStreamPlayer : public LiveStreamable, public VideoRecordable
{
    bool liveStarted{false};
    bool playing{false};

public:
    void record(const string &dest) override { (void)dest; /* pretend */ }
    void streamLive(const string &url) override
    {
        (void)url;
        liveStarted = true;
    }
    bool isPlaying() const { return playing; }
    bool isLive() const { return liveStarted; }
};

int main()
{
    AudioPlayer ap;
    ap.play("song.mp3");
    cout << "Audio playing: " << boolalpha << ap.isPlaying() << "\n";
    ap.pause();

    CameraStreamPlayer cam;
    cam.streamLive("rtsp://camera"); // required order

    return 0;
}
