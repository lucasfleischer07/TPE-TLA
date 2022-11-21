package com.example.java;

import com.example.java.OutputUtils;
import org.jfugue.player.Player;
public class Out {
	public static void main(String[] args) {
		OutputUtils outputUtils = new OutputUtils();
		String outputString = outputUtils.defineSong();
		String track1 = outputUtils.defineTrack();
		String nota1 = new String();
		String nota2 = new String();
		String nota3 = new String();
		String song1 = outputUtils.defineSong();
		nota1 = outputUtils.modifyNote("D", "q", 3);
		nota2 = outputUtils.modifyNote("C", "h", 4);
		nota3 = outputUtils.modifyNote("E", "i", 5);
		track1 = outputUtils.trackAddNote(track1, nota1);
		track1 = outputUtils.trackAddNote(track1, nota1);
		track1 = outputUtils.trackAddNote(track1, nota2);
		track1 = outputUtils.trackAddNote(track1, nota3);
		song1 = outputUtils.songAddTrack(song1, track1);
		track1 = outputUtils.trackSubstraction(track1, nota1);
		track1 = outputUtils.trackSubstraction(track1, nota2);
		Player player = new Player();
		player.play(outputString);
	}
}
