package com.example.java;
import com.example.java.OutputUtils;
import org.jfugue.player.Player;
public class Output {
    public static void main(String[] args) {
        OutputUtils outputUtils=new OutputUtils();
        String song= outputUtils.defineSong();
        String track1= outputUtils.defineTrack();
        String track2=outputUtils.defineTrack();
        String note1=new String("");
        String note2=new String("");
        String note3=new String("");
        note1=outputUtils.modifyNote("B");
        note2=outputUtils.modifyNote("C","q");
        note3=outputUtils.modifyNote("C","q",5);
        track1= outputUtils.changeInstrument(track1,Instruments.values()[1]);
        track1= outputUtils.trackAddNote(track1,note2);
        track1=outputUtils.trackAddNote(track1,note3);
        track1=outputUtils.trackAddNote(track1,note1);
        track1=outputUtils.trackSubstraction(track1,note1);
        track1= outputUtils.trackMultiply(track1,8);
        track2=outputUtils.trackAddNote(track2,note1);
        track2=outputUtils.trackAddNote(track2,note2);
        track2=outputUtils.trackMultiply(track2,6);
        track2= outputUtils.trackDivision(track2,note1);
        track2=outputUtils.changeInstrument(track2,Instruments.values()[1]);
        song=outputUtils.songAddTrack(song,track1);
        song=outputUtils.songAddTrack(song,track2);
        song=outputUtils.changeTempo(song,1.5);
        Player player=new Player();
        player.play(song);

    }
}
