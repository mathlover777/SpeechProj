import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;
import javax.swing.border.EtchedBorder;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;

import static java.nio.file.StandardCopyOption.*;

import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JTextArea;
import javax.swing.JButton;
import javax.swing.JScrollBar;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;


public class GUI_interface extends JFrame {

	private JPanel contentPane;
	private JMenu mnFile;
	private JMenu mnAbout;
	private JMenuItem mntmDefault;
	private JMenuItem mntmOpen;
	private JTextArea txtrTextarea;
	private JScrollBar scrollBar;
	private JButton btnDone;
	private JButton btnExit;	
	private double preemphasis;
	private double overlappercent;
	private int framesize;
	private int LPCorder;
	private int F0;
	private String filename; 
	private JButton btnDefaultParameters;
	private JButton btnSetparam;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					GUI_interface frame = new GUI_interface();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public GUI_interface() {
		try {
			UIManager.setLookAndFeel("com.sun.java.swing.plaf.gtk.GTKLookAndFeel");
		} catch (ClassNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (InstantiationException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (IllegalAccessException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (UnsupportedLookAndFeelException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		setTitle("LPC-Encoder&Decoder");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 505, 329);
		contentPane = new JPanel();
		contentPane.setBorder(new TitledBorder(new EtchedBorder(EtchedBorder.LOWERED, new Color(0, 0, 0), new Color(255, 175, 175)), "", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JMenuBar menuBar = new JMenuBar();
		menuBar.setBounds(0, 0, 489, 21);
		contentPane.add(menuBar);
		
		mnFile = new JMenu("File");
		menuBar.add(mnFile);
		
		mntmDefault = new JMenuItem("Default");
		mnFile.add(mntmDefault);
		
		mntmOpen = new JMenuItem("Open");
		mnFile.add(mntmOpen);
		
		mnAbout = new JMenu("About");
		menuBar.add(mnAbout);
		
		txtrTextarea = new JTextArea();
		txtrTextarea.setBounds(10, 32, 307, 192);
		contentPane.add(txtrTextarea);
		
		btnDefaultParameters = new JButton("Default Parameters");
		btnDefaultParameters.setBounds(348, 106, 131, 23);
		contentPane.add(btnDefaultParameters);
		
		btnSetparam = new JButton("Set Parameters");
		btnSetparam.setBounds(348, 141, 131, 23);
		contentPane.add(btnSetparam);
		
		scrollBar = new JScrollBar();
		scrollBar.setRequestFocusEnabled(true);
		scrollBar.setBounds(300, 32, 17, 192);
		contentPane.add(scrollBar);
		
		btnDone = new JButton("Done");
		btnDone.setBounds(242, 246, 101, 23);
		contentPane.add(btnDone);
		
		btnExit = new JButton("Exit");
		btnExit.setBounds(364, 246, 101, 23);
		contentPane.add(btnExit);
		
		btnExit.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				dispose();
				
				
			}
		}); 
		btnDone.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				
				//./run wavfile.txt outputwav1.txt outputwav2.txt outputwav3.txt 0.95 5 50 17 6
				String s;
				s="./run "+filename+" outputwav1.txt outputwav2.txt outputwav3.txt "+Double.toString(preemphasis)+" "+Integer.toString(((int)overlappercent*framesize)/100)+" "+Integer.toString(framesize)+" "+Integer.toString(LPCorder)+" "+Integer.toString(16/F0);
				System.out.println(s);
				try {

					// You can execute a process and get a Process
					// object back.
					Process myProc =
						Runtime.getRuntime().exec(s);

					// From the Processs Object you can get an InputStream
					// (InputStream is what you want, not OutputStream,
					// despite the name)
					InputStream is = myProc.getInputStream();

					// Send your InputStream to an InputStreamReader:
					InputStreamReader isr = new InputStreamReader(is);

					// That needs to go to a BufferedReader:
					BufferedReader br = new BufferedReader(isr);

					// And now, finally, we can get some strings
					// back:
					while (br.ready()) {
						System.out.println(br.readLine());
					}


					// Other interesting things:
					//
					// the process must be finished before we can
					// determine the exit value:
					myProc.waitFor();
					int myProcExitVal = myProc.exitValue();

					System.out.println("\n\n");
					System.out.println("=== Process Finished ===");
					System.out.println("Exit Value: " + myProcExitVal);


				} catch (IOException e) {

					// I haven't figured out how to trip this yet.
					// Which makes sense. Java doesn't really know
					// if your process failed. That must be determined
					// from the exit value.
					System.out.println("Houston we have uhoh: "+e);
				} catch (InterruptedException e) {
					
					// You need this for that waitFor() diddy.
					System.out.println("Something got interrupted, "+
						"I guess: "+e);
				}
			}
		}); 
		
		btnDefaultParameters.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				preemphasis=0.95;
				overlappercent=10;
				framesize=400;
				LPCorder=16;
				GetF0 obj=new GetF0();
				obj.setVisible(true);
				F0=obj.F0;
				
				 
				
			}
		});
		btnSetparam.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				
				SetParam obj = new SetParam();
				obj.setVisible(true);
				preemphasis=obj.preEmphasis;
				overlappercent=obj.overLap;
				framesize=obj.frameSize;
				LPCorder=obj.LPCorder;
				F0=obj.F0;
				
				
			}
		}); 
		
		mntmDefault.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				filename="wavfile.txt";
				
				
			}
		}); 
		mntmOpen.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				
				File open=null;
				String path;
				Path path1,path2;
			    JDialog opt=new JDialog();
				opt.setTitle("Choose folder to open");
				JFileChooser chooser = new JFileChooser();
				chooser.setFileSelectionMode(JFileChooser.OPEN_DIALOG);  
				int result = chooser.showOpenDialog(opt);
				if (result == chooser.APPROVE_OPTION) { 
				      open=chooser.getSelectedFile();
				      
				   }
				if(open==null)
					return;
				 path=open.getAbsolutePath();
				 path=path.substring(0, path.lastIndexOf('/'));
				 String temp=open.getName();
				 filename=temp;
				 path1= FileSystems.getDefault().getPath(path,temp);
				 path2= FileSystems.getDefault().getPath("", "wavfile.txt");
				 			 
				 try {
					Files.copy(path1, path2, REPLACE_EXISTING);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
		});
		
		
		
		
		
	}
}
