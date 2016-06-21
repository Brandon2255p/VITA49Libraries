package nxm.vrt.libm;

import nxm.vrt.lib.BasicDataPacket;
import nxm.vrt.lib.BasicVRTPacket;

public class StandardContextPacket extends BasicDataPacket
{
	private static byte[] StandardContextPacket_createDefaultPacket () {
		  byte[] buf = new byte[32];
		  buf[0] = 72;
		  buf[1] = -96;
		  buf[2] = 0;
		  buf[3] = 8;
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
		  buf[15] = 3;
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
		public static final PacketType PACKET_TYPE = PacketType.Context;
		public static final int PACKET_LENGTH = -4;
		public static final long CLASS_IDENTIFIER = 0xFFFFFA20110003L;
		public static final String CLASS_ID = "FF-FF-FA:2011.0003";

		//======================================================================
		// PACKET TYPE CONSTRUCTORS
		//======================================================================
		public StandardContextPacket () {
			super(StandardContextPacket_createDefaultPacket(), 0, StandardContextPacket_createDefaultPacket().length ,false, false);
		}

		public StandardContextPacket (byte[] bbuf, boolean readOnly) {
			super(bbuf, 0, bbuf.length ,readOnly, false);
		}

		public StandardContextPacket (BasicVRTPacket p, boolean copy) {
			super(p, copy);
		}

		public StandardContextPacket (BasicVRTPacket p, PacketType type, long classID, int minPayloadLength, int maxPayloadLength) {
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
}
