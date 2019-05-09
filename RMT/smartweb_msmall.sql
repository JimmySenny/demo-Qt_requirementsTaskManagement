-- t_vers_info  �汾��Ϣ��
CREATE TABLE `t_vers_info`
(
    `id` varchar(32) NOT NULL COMMENT '����ID',
    `ver_no` varchar(50) NOT NULL COMMENT '�汾��',
    `sys_id` char(4) NOT NULL COMMENT '����ϵͳID',
    `ver_name` varchar(128) NOT NULL COMMENT '�汾���ļ�����',
    `src_name` varchar(128) DEFAULT NULL COMMENT 'ԭʼ���ļ�����',
    `doc_name` varchar(128) DEFAULT NULL COMMENT '�����ĵ�����',
    `dtalst_id` varchar(128) DEFAULT NULL COMMENT '��ڿ���DTA�б�ID',
    `alalst_id` varchar(128) DEFAULT NULL COMMENT '�漰ALA�б�ID',
    `ver_type` char(1) NOT NULL COMMENT '�汾����',
    `ref_type` char(1) NOT NULL COMMENT '��Ч����',
    `ver_path` varchar(128) NOT NULL COMMENT '�汾����·��',
    `chk_user` varchar(64) NOT NULL COMMENT '����û�ID',
    `dep_flag` char(1) NOT NULL COMMENT '�����־',
    `ref_flag` char(1) NOT NULL COMMENT '��Ч��־',
    `redo_flag` char(1) NOT NULL COMMENT '���˱�־',
    `com_flag` char(1) NOT NULL COMMENT '�Ƿ��漰����',
    `stat` char(1) NOT NULL COMMENT '�汾״̬',
    `create_by` varchar(64) DEFAULT NULL COMMENT '������',
    `create_date` varchar(20) DEFAULT NULL COMMENT '����ʱ��',
    `update_by` varchar(64) DEFAULT NULL COMMENT '������',
    `update_date` varchar(20) DEFAULT NULL COMMENT '����ʱ��',
    `del_flag` char(1) DEFAULT NULL COMMENT 'ɾ����־',
    `rmrk1` varchar(100) DEFAULT NULL COMMENT '�����ֶ�1',
    `rmrk2` varchar(100) DEFAULT NULL COMMENT '�����ֶ�2',
    `rmrk3` varchar(300) DEFAULT NULL COMMENT '�����ֶ�3',
    `rmrk4` varchar(300) DEFAULT NULL COMMENT '�����ֶ�4',
    `remarks` varchar(255) DEFAULT NULL COMMENT '��ע��Ϣ'
) COMMENT='�汾��Ϣ��';

ALTER TABLE `t_vers_info` ADD PRIMARY KEY (id);

ALTER TABLE `t_vers_info` ADD UNIQUE (ver_no);


-- tb_rmt_user  �û���Ϣ��
CREATE TABLE `tb_rmt_user`
(
    `user_id` varchar(16) NOT NULL COMMENT '�û�ID',
    `user_name` varchar(60) NOT NULL COMMENT '�û�����',
    `user_pwd` varchar(16) NOT NULL COMMENT '�û�����',
    `user_level` char(2) DEFAULT NULL COMMENT '�û�����',
    `user_depm` char(2) DEFAULT NULL COMMENT '�û���ڲ���',
    `user_team` char(2) DEFAULT NULL COMMENT '�û�����Ŷ�',
    `user_status` char(2) NOT NULL COMMENT '�û�״̬',
    `rmrk1` varchar(100) DEFAULT NULL COMMENT '�����ֶ�1',
    `rmrk2` varchar(100) DEFAULT NULL COMMENT '�����ֶ�2',
    `rmrk3` varchar(300) DEFAULT NULL COMMENT '�����ֶ�3',
    `rmrk4` varchar(300) DEFAULT NULL COMMENT '�����ֶ�4',
    `dac` varchar(16) DEFAULT NULL COMMENT 'DAC�ֶ�'
) COMMENT='�û���Ϣ��';

ALTER TABLE `tb_rmt_user` ADD PRIMARY KEY (user_id);



-- tb_rmt_enum  ö����Ϣ��
CREATE TABLE `tb_rmt_enum`
(
    `enum_name` char(50) DEFAULT NULL COMMENT 'ö������',
    `enum_status` char(2) DEFAULT NULL COMMENT 'ö�ټ�¼״̬',
    `enum_key` char(50) DEFAULT NULL COMMENT 'ö�ټ�ֵ',
    `enum_value` char(100) DEFAULT NULL COMMENT 'ö��ֵ',
    `rmrk1` varchar(100) DEFAULT NULL COMMENT '�����ֶ�1',
    `rmrk2` varchar(100) DEFAULT NULL COMMENT '�����ֶ�2',
    `rmrk3` varchar(300) DEFAULT NULL COMMENT '�����ֶ�3',
    `rmrk4` varchar(300) DEFAULT NULL COMMENT '�����ֶ�4',
    `dac` varchar(16) DEFAULT NULL COMMENT 'DAC�ֶ�'
) COMMENT='ö����Ϣ��';




-- tb_rmt_requirements  ���������Ϣ��
CREATE TABLE `tb_rmt_requirements`
(
    `uuid` char(32) NOT NULL COMMENT 'uuid',
    `req_no` varchar(32) NOT NULL COMMENT '������',
    `req_type` char(2) NOT NULL COMMENT '��������',
    `sys_attr` char(2) NOT NULL COMMENT '��������',
    `req_name` varchar(128) NOT NULL COMMENT '�������',
    `req_desc` varchar(1024) DEFAULT NULL COMMENT '��������',
    `req_dpm` varchar(20) DEFAULT NULL COMMENT '�����������',
    `req_busiop` varchar(16) DEFAULT NULL COMMENT '���󾭰���',
    `req_inputdt` char(19) DEFAULT NULL COMMENT '�����ύʱ��',
    `req_expectdt` char(19) DEFAULT NULL COMMENT '��������ʱ��',
    `req_busicheck` varchar(16) DEFAULT NULL COMMENT '���������',
    `req_checkdt` char(19) DEFAULT NULL COMMENT '�������ʱ��',
    `req_level` char(1) DEFAULT NULL COMMENT '�������ȼ�',
    `req_disop` varchar(16) DEFAULT NULL COMMENT '���������',
    `req_disdt` char(19) DEFAULT NULL COMMENT '�������ʱ��',
    `req_team` varchar(20) DEFAULT NULL COMMENT '����ǣͷ�Ŷ�',
    `req_teamlader` varchar(16) DEFAULT NULL COMMENT '����ǣͷ�ŶӸ�����',
    `req_system` varchar(10) DEFAULT NULL COMMENT '����ǣͷϵͳ',
    `req_tecoperator` varchar(16) DEFAULT NULL COMMENT '����ǣͷ������',
    `req_relation` varchar(100) DEFAULT NULL COMMENT '�������ϵͳ',
    `req_stat` char(2) DEFAULT NULL COMMENT '����ǰ�׶�',
    `req_plandt` char(19) DEFAULT NULL COMMENT '����ƻ����ʱ��',
    `req_donedt` char(19) DEFAULT NULL COMMENT '����ƻ�ʵ��ʱ��',
    `rmrk1` varchar(100) DEFAULT NULL COMMENT '�����ֶ�1',
    `rmrk2` varchar(100) DEFAULT NULL COMMENT '�����ֶ�2',
    `rmrk3` varchar(300) DEFAULT NULL COMMENT '�����ֶ�3',
    `rmrk4` varchar(300) DEFAULT NULL COMMENT '�����ֶ�4',
    `dac` varchar(16) DEFAULT NULL COMMENT 'DAC�ֶ�'
) COMMENT='���������Ϣ��';

ALTER TABLE `tb_rmt_requirements` ADD PRIMARY KEY (uuid);

ALTER TABLE `tb_rmt_requirements` ADD UNIQUE (req_no);


-- tb_rmt_task  ���������Ϣ��
CREATE TABLE `tb_rmt_task`
(
    `uuid` char(32) NOT NULL COMMENT 'uuid',
    `req_no` varchar(32) NOT NULL COMMENT '����������',
    `task_no` varchar(32) NOT NULL COMMENT '������',
    `task_type` char(2) DEFAULT NULL COMMENT '��������',
    `task_attr` char(2) DEFAULT NULL COMMENT '��������',
    `task_name` varchar(128) DEFAULT NULL COMMENT '�������',
    `task_desc` varchar(1024) DEFAULT NULL COMMENT '��������',
    `task_inputdt` char(19) DEFAULT NULL COMMENT '�������ʱ��',
    `task_expectdt` char(19) DEFAULT NULL COMMENT '������������ʱ��',
    `task_level` char(1) DEFAULT NULL COMMENT '�������ȼ�',
    `task_team` varchar(20) DEFAULT NULL COMMENT '��������Ŷ�',
    `task_teamlader` varchar(16) DEFAULT NULL COMMENT '��������ŶӸ�����',
    `task_system` varchar(10) DEFAULT NULL COMMENT '�������ϵͳ',
    `task_tecop` varchar(16) DEFAULT NULL COMMENT '������������',
    `task_stat` char(2) DEFAULT NULL COMMENT '����ǰ�׶�',
    `task_plandt` char(19) DEFAULT NULL COMMENT '����ƻ����ʱ��',
    `task_donedt` char(19) DEFAULT NULL COMMENT '����ʵ�����ʱ��',
    `task_partyop` varchar(16) DEFAULT NULL COMMENT '����������̸�����',
    `rmrk1` varchar(100) DEFAULT NULL COMMENT '�����ֶ�1',
    `rmrk2` varchar(100) DEFAULT NULL COMMENT '�����ֶ�2',
    `rmrk3` varchar(300) DEFAULT NULL COMMENT '�����ֶ�3',
    `rmrk4` varchar(300) DEFAULT NULL COMMENT '�����ֶ�4',
    `dac` varchar(16) DEFAULT NULL COMMENT 'DAC�ֶ�'
) COMMENT='���������Ϣ��';

ALTER TABLE `tb_rmt_task` ADD PRIMARY KEY (uuid);

ALTER TABLE `tb_rmt_task` ADD UNIQUE (task_no);

ALTER TABLE `tb_rmt_task` ADD INDEX index_name(req_no);

