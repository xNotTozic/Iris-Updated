#pragma once

void SendToServerDetour(LoopbackPacketSender* _this, Packet* packet) {
    bool cancelled = false;

    PacketSendingEvent event(packet); // probably gonan fix this up too cuz it looks bad
    event.cancelled = &cancelled;
    DispatchEvent(&event);

    if (packet && packet->instanceOf<PlayerAuthInputPacket>()) {
        PlayerAuthInputPacket* pkt = (PlayerAuthInputPacket*)packet;
        if (pkt) {
            Game::Core::bodyYaw = pkt->yaw;
            Game::Core::headYaw = pkt->yawUnused;
            Game::Core::pitch = pkt->pitch;
        }
    }
    if (packet && packet->instanceOf<MovePlayerPacket>()) {
        MovePlayerPacket* pkt = reinterpret_cast<MovePlayerPacket*>(packet);
        if (pkt) {
            Game::Core::bodyYaw = pkt->yaw;
            Game::Core::headYaw = pkt->headYaw;
            Game::Core::pitch = pkt->pitch;
        }
    }

    if (!cancelled)
    {
        CallFunc<void*, LoopbackPacketSender*, Packet*>(
            __o__SendPacket,
            _this,
            packet
        );
    }
}