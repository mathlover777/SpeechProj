import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import javax.swing.JTextField;


public class GetF0 extends JDialog {

	private final JPanel contentPanel = new JPanel();
	private JTextField f0;
	private JButton btnOK;
	
	public int F0;

	/**
	 * Launch the application.
	 */
	/*
	public static void main(String[] args) {
		try {
			GetF0 dialog = new GetF0();
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
	public GetF0() {
		setModal(true);
		setTitle("Enter F0");
		setBounds(100, 100, 363, 216);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
		
		JLabel lblEnterF = new JLabel("Enter F0(in kHz):");
		lblEnterF.setBounds(54, 63, 111, 20);
		contentPanel.add(lblEnterF);
		
		f0 = new JTextField();
		f0.setBounds(162, 62, 86, 23);
		contentPanel.add(f0);
		f0.setColumns(10);
		{
			JPanel buttonPane = new JPanel();
			buttonPane.setLayout(new FlowLayout(FlowLayout.RIGHT));
			getContentPane().add(buttonPane, BorderLayout.SOUTH);
			{
				btnOK = new JButton("OK");
				btnOK.setActionCommand("OK");
				buttonPane.add(btnOK);
				getRootPane().setDefaultButton(btnOK);
			}
		}
		
		btnOK.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				try{
						
						F0=Integer.parseInt(f0.getText());
						dispose();
				}catch(NumberFormatException e){
					JOptionPane.showMessageDialog(null,"Invalid entry");
				}
				
				
				
			}
		});
		
		
		
		
	}
}
