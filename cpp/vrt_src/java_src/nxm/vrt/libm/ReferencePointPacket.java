package nxm.vrt.libm;

import nxm.vrt.lib.AsciiCharSequence;
import nxm.vrt.lib.BasicDataPacket;
import nxm.vrt.lib.BasicVRTPacket;
public class ReferencePointPacket extends BasicDataPacket
{
	//======================================================================
	// NON-CLASS METHODS
	//======================================================================
	/** Creates the default header for the packet. This is defined separate
	 *  from the class to account for the systems/compilers that disallow
	 *  calling of subclass methods from the constructor.
	 */
	private static byte[] ReferencePointPacket_createDefaultPacket () {
	  byte[] buf = new byte[68];
	  buf[0] = 88;
	  buf[1] = -96;
	  buf[2] = 0;
	  buf[3] = 17;
	  buf[4] = 0;
	  buf[5] = 0;
	  buf[6] = 0;
	  buf[7] = 0;
	  buf[8] = 0;
	  buf[9] = -1;
	  buf[10] = -1;
	  buf[11] = -6;
	  buf[12] = 32;
	  buf[13] = 17;
	  buf[14] = 0;
	  buf[15] = 6;
	  buf[16] = 0;
	  buf[17] = 0;
	  buf[18] = 0;
	  buf[19] = 0;
	  buf[20] = 0;
	  buf[21] = 0;
	  buf[22] = 0;
	  buf[23] = 0;
	  buf[24] = 0;
	  buf[25] = 0;
	  buf[26] = 0;
	  buf[27] = 0;
	  return buf;
	}

	//======================================================================
	// PACKET TYPE STATIC CONSTANTS
	//======================================================================
	public static final PacketType PACKET_TYPE = PacketType.ExtContext;
	public static final int PACKET_LENGTH = -40;
	public static final long CLASS_IDENTIFIER = 0xFFFFFA20110006L;
	public static final String CLASS_ID = "FF-FF-FA:2011.0006";


	//======================================================================
	// PACKET TYPE CONSTRUCTORS
	//======================================================================
	public ReferencePointPacket () {
		super(ReferencePointPacket_createDefaultPacket(), 0, ReferencePointPacket_createDefaultPacket().length ,false, false);
	}

	public ReferencePointPacket (byte[] bbuf, boolean readOnly) {
		super(bbuf, 0, bbuf.length ,readOnly, false);
	}

	public ReferencePointPacket (BasicVRTPacket p, boolean copy) {
		super(p, copy);
	}

	public ReferencePointPacket (BasicVRTPacket p, PacketType type, long classID, int minPayloadLength, int maxPayloadLength) {
		super(p, false);
	 // Not done
	}

	//======================================================================
	// UTILITY METHODS
	//======================================================================
	@Override
	public String getPacketValid (boolean strict, int length) {
		String err = super.getPacketValid(strict, length);
	  if (err != "") {
		return err;
	  }

	  boolean okType = (getPacketType() == PACKET_TYPE);
	  boolean okID   = (getClassIdentifier() == CLASS_IDENTIFIER);

	  if (!okType) {
		String str = "Invalid use of " + this.getClass().getName() + " with " + getPacketType() + "packet.";
		return str;
	  }
	  if (!okID) {
		String str = "Invalid use of " + this.getClass().getName() + " with ClassID=" + getClassID() + ".";
		return str;
	  }
	  return "";
	}

	@Override
	protected StringBuilder toStringBuilder () {
		StringBuilder str = super.toStringBuilder();
		str.append(" RefPointID=" + getRefPointID());
		str.append(" Name='" + getName() + "'");
		str.append(" Description='" + getDescription() + "'");
		return str;
	}

	@Override
	public int getFieldCount () {
		return super.getFieldCount() + 0;
	}

	@Override
	  public String getFieldName (int id) {
		switch (id - super.getFieldCount()) {
		    default: return super.getFieldName(id);
		  }
	  }

	@Override
	public Class<?> getFieldType (int id) {
	  switch (id - super.getFieldCount()) {
	    default: return super.getFieldType(id);
	  }
	}

	@Override
	public Object getField (int id) {
	  switch (id - super.getFieldCount()) {
	    default: return super.getField(id);
	  }
	}

	@Override
	public void setField (int id, Object val) {
	  switch (id - super.getFieldCount()) {
	    default: super.setField(id,val); break;
	  }
	}

	//======================================================================
    // GET/SET METHODS
    //======================================================================

    /** Get the reference point identifier.
     *  @return The value read from the packet.
     */
    public int getRefPointID () {
      return unpackPayloadInt(0);
    }

    /** Set the reference point identifier.
     *  @param val The new value to write to the packet.
     */
    public void setRefPointID (int val) {
      packPayloadInt(0, val);
    }

    /** Get A free-form name of the reference point.
     *  <br> Size: <tt>32</tt>
     *  @return The value read from the packet.
     */
    public AsciiCharSequence getName () {
      return unpackPayloadAscii(8, 32);
    }

    /** Set A free-form name of the reference point.
     *  <br> Size: <tt>32</tt>
     *  @param val The new value to write to the packet.
     *             Any non-ASCII characters in the string (numeric value &gt;0x7F) or ASCII
     *             control characters (numeric value &lt;0x20, 0x7F) will be replaced with '?'.
     *             If the string is longer than the size allotted, it will be
     *             truncated without warning.
     */
    public void setName (String val) {
      packPayloadAscii(8, val, 32);
    }

    /** Get A free-form description of the reference point.
     *  <br> Size: <tt>variable</tt>
     *  @return The value read from the packet.
     */
    public CharSequence getDescription () {
      return unpackPayloadUTF8(40, getPayloadLength()-40);
    }

    /** Set A free-form description of the reference point.
     *  <br> Size: <tt>variable</tt>
     *  @param val The new value to write to the packet.
     */
    public void setDescription (CharSequence val) {
    int limit  = MAX_PAYLOAD_LENGTH-40;
    int length = nxm.vrt.lib.VRTMath.lengthUTF8(val);
    int len    = (length > limit)? ((limit  + 3) & 0x7FFFFFFC)
                                     : ((length + 3) & 0x7FFFFFFC); // length to next multiple of 4
      setPayloadLength(40 + len);
      packPayloadUTF8(40, val, len);
    }

    /** Set A free-form description of the reference point.
     *  <br> Size: <tt>variable</tt>
     *  @param val The new value to write to the packet.
     */
    public void setDescription (AsciiCharSequence val) {
    int limit  = MAX_PAYLOAD_LENGTH-40;
    int length = nxm.vrt.lib.VRTMath.lengthUTF8(val);
    int len    = (length > limit)? ((limit  + 3) & 0x7FFFFFFC)
                                     : ((length + 3) & 0x7FFFFFFC); // length to next multiple of 4
      setPayloadLength(40 + len);
      packPayloadUTF8(40, val, len);
    }
}
