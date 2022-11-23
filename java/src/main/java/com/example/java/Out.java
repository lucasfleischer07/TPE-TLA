package com.example.java;

import com.example.java.OutputUtils;
import org.jfugue.player.Player;
public class Out {
	public static void main(String[] args) {
		OutputUtils outputUtils = new OutputUtils();
		String nota1 = new String();
		String nota2 = new String();
		String nota3 = new String();
		String nota4 = new String();
		String track1 = outputUtils.defineTrack();
		String track2 = outputUtils.defineTrack();
		String song1 = outputUtils.defineSong();
		nota1 = outputUtils.modifyNote("D", "q", 5);
		nota2 = outputUtils.modifyNote("C", "q", 5);
		nota3 = outputUtils.modifyNote("E", "q", 5);
		nota4 = outputUtils.modifyNote("R", "q");
		track1 = outputUtils.trackAddNote(track1, nota1);
		track1 = outputUtils.trackAddNote(track1, nota1);
		track1 = outputUtils.trackAddNote(track1, nota2);
		track1 = outputUtils.trackAddNote(track1, nota3);
		track1 = outputUtils.changeInstrument(track1, 0);
		track2 = outputUtils.trackAddNote(track2, nota4);
		track2 = outputUtils.trackAddNote(track2, nota4);
		track2 = outputUtils.trackAddNote(track2, nota4);
		track2 = outputUtils.trackAddNote(track2, nota4);
		track2 = outputUtils.trackAddNote(track2, nota4);
		track2 = outputUtils.trackAddNote(track2, nota1);
		track2 = outputUtils.trackAddNote(track2, nota1);
		track2 = outputUtils.trackAddNote(track2, nota2);
		track2 = outputUtils.trackAddNote(track2, nota3);
		track2 = outputUtils.changeInstrument(track2, 1);
		song1 = outputUtils.songAddTrack(song1, track1);
		song1 = outputUtils.songAddTrack(song1, track2);
		Player player = new Player();
		player.play(song1);
	}
}
