# 02-media-lsp-isp.py
# Messy starter: Fat interface + LSP surprises (violates ISP + LSP)

from abc import ABC, abstractmethod

class Player(ABC):
    @abstractmethod
    def play(self, source: str) -> None:
        pass
    
    @abstractmethod
    def pause(self) -> None:
        pass
    
    @abstractmethod
    def record(self, destination: str) -> None:  # many can't
        pass
    
    @abstractmethod
    def stream_live(self, url: str) -> None:  # many can't
        pass
    
    @abstractmethod
    def download(self, source_url: str) -> None:  # many can't
        pass

class AudioPlayer(Player):
    def __init__(self):
        self.playing = False
    
    def play(self, source: str) -> None:
        self.playing = True
    
    def pause(self) -> None:
        self.playing = False
    
    def record(self, destination: str) -> None:  # LSP break
        raise NotImplementedError("AudioPlayer cannot record")
    
    def stream_live(self, url: str) -> None:  # LSP break
        raise NotImplementedError("AudioPlayer cannot stream_live")
    
    def download(self, source_url: str) -> None:
        # pretend download
        pass
    
    def is_playing(self) -> bool:
        return self.playing

class CameraStreamPlayer(Player):
    def __init__(self):
        self.live_started = False
        self.playing = False
    
    def play(self, source: str) -> None:
        # Surprise: needs stream_live first for "real" play
        if not self.live_started:
            print("[WARN] playing without live stream started.")
        self.playing = True
    
    def pause(self) -> None:
        self.playing = False
    
    def record(self, destination: str) -> None:
        # pretend record
        pass
    
    def stream_live(self, url: str) -> None:
        self.live_started = True
    
    def download(self, source_url: str) -> None:  # LSP break
        raise NotImplementedError("CameraStreamPlayer cannot download")
    
    def is_playing(self) -> bool:
        return self.playing
    
    def is_live(self) -> bool:
        return self.live_started

def main():
    ap = AudioPlayer()
    ap.play("song.mp3")
    print(f"Audio playing: {ap.is_playing()}")
    ap.pause()

    cam = CameraStreamPlayer()
    cam.play("rtsp://camera")       # warning surprise
    cam.stream_live("rtsp://camera")  # required order
    cam.play("rtsp://camera")
    
    try:
        cam.download("http://file")
    except Exception as e:
        print(f"[EXC] {e}")

if __name__ == "__main__":
    main()