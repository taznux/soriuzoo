package uzoo.io;

import java.io.IOException;

public interface Writable 
{
	public void write( byte[] b ) throws IOException;

	public void write( byte[] b, int off, int len ) throws IOException;

	public void write( int b ) throws IOException;

	public void closeOut();
}
