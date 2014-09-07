import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.JComboBox;
import javax.swing.DefaultComboBoxModel;


public class SetParam extends JDialog {

	private final JPanel contentPanel = new JPanel();
	private JTextField preemph;
	private JTextField framesz;
	private JComboBox overlap;
	private JComboBox LPC;
	private JTextField f0;
	
	public double preEmphasis;
	public int frameSize;
	public double overLap;
	public int LPCorder;
	public int F0;
	private JButton btnOk;
	private JButton btnCancel;

	/**
	 * Launch the application.
	 */
	/*
	public static void main(String[] args) {
		try {
			SetParam dialog = new SetParam();
			dialog.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			dialog.setVisible(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	*/
	/**
	 * Create the dialog.
	 */
	public SetParam() {
		setModal(true);
		setTitle("Set Parameters");
		setBounds(100, 100, 460, 325);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
		
		JLabel lblPreemphasis = new JLabel("PreEmphasis");
		lblPreemphasis.setBounds(83, 11, 86, 19);
		contentPanel.add(lblPreemphasis);
		
		preemph = new JTextField();
		preemph.setBounds(206, 10, 86, 20);
		contentPanel.add(preemph);
		preemph.setColumns(10);
		
		JLabel lblFramesize = new JLabel("FrameSize");
		lblFramesize.setBounds(83, 47, 86, 14);
		contentPanel.add(lblFramesize);
		
		framesz = new JTextField();
		framesz.setBounds(206, 44, 86, 20);
		contentPanel.add(framesz);
		framesz.setColumns(10);
		
		JLabel lblPercentoverlap = new JLabel("PercentOverlap");
		lblPercentoverlap.setBounds(83, 84, 86, 14);
		contentPanel.add(lblPercentoverlap);
		
		overlap = new JComboBox();
		overlap.setModel(new DefaultComboBoxModel(new String[] {"0", "10", "20", "30", "40", "50", "60", "70", "80", "90"}));
		overlap.setBounds(249, 81, 42, 20);
		contentPanel.add(overlap);
		
		JLabel lblLpcOrder = new JLabel("LPC Order");
		lblLpcOrder.setBounds(83, 128, 86, 14);
		contentPanel.add(lblLpcOrder);
		
		LPC = new JComboBox();
		LPC.setModel(new DefaultComboBoxModel(new String[] {"12", "13", "14", "15", "16", "17", "18", "19", "20"}));
		LPC.setSelectedIndex(4);
		LPC.setBounds(249, 125, 43, 20);
		contentPanel.add(LPC);
		
		JLabel lblF = new JLabel("F0(in kHz)");
		lblF.setBounds(83, 176, 86, 14);
		contentPanel.add(lblF);
		
		f0 = new JTextField();
		f0.setBounds(206, 173, 86, 20);
		contentPanel.add(f0);
		f0.setColumns(10);
		{
			JPanel buttonPane = new JPanel();
			buttonPane.setLayout(new FlowLayout(FlowLayout.RIGHT));
			getContentPane().add(buttonPane, BorderLayout.SOUTH);
			{
				btnOk = new JButton("OK");
				btnOk.setActionCommand("OK");
				buttonPane.add(btnOk);
				getRootPane().setDefaultButton(btnOk);
			}
			{
				btnCancel = new JButton("Cancel");
				btnCancel.setActionCommand("Cancel");
				buttonPane.add(btnCancel);
			}
		}
		
		btnCancel.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				
				preEmphasis=0.95;
				frameSize=400;
				overLap=10;
				LPCorder=16;
				F0=3;
				dispose();
				
				
				
			}
		});
		btnOk.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				try{
						preEmphasis=Double.parseDouble(preemph.getText());
						frameSize=Integer.parseInt(framesz.getText());
						overLap=(overlap.getSelectedIndex())*10;
						LPCorder=LPC.getSelectedIndex()+12;
						F0=Integer.parseInt(f0.getText());
						dispose();
				}catch(NumberFormatException e){
					JOptionPane.showMessageDialog(null,"Invalid entry");
				}
				
				
				
			}
		});
	}
}
